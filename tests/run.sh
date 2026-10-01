#!/usr/bin/env bash
# Feeds scripted input to tsh on stdin and checks stdout and exit status.
# Usage: tests/run.sh [path/to/tsh]

TSH=${1:-./tsh}
# run tsh with a fixed environment so env/setenv output is deterministic
CWD=$(pwd -P)
ENV="PATH=/usr/bin:/bin HOME=/tmp PWD=$CWD"
BASE=$'PATH=/usr/bin:/bin\nHOME=/tmp\nPWD='"$CWD"
pass=0
fail=0

# check NAME INPUT EXPECTED_STDOUT EXPECTED_STATUS
check() {
  local name=$1 input=$2 want_out=$3 want_status=$4 out status
  out=$(printf '%b' "$input" | env -i $ENV "$TSH" 2>/dev/null)
  status=$?
  if [ "$out" == "$want_out" ] && [ "$status" == "$want_status" ]; then
    pass=$((pass + 1))
  else
    fail=$((fail + 1))
    printf 'FAIL: %s\n' "$name"
    printf '  want (status %s): %.120q\n' "$want_status" "$want_out"
    printf '  got  (status %s): %.120q\n' "$status" "$out"
  fi
}

# command execution
check "run from PATH"            'echo hello world\n'          'hello world' 0
check "run absolute path"        '/bin/echo abs\n'             'abs' 0
check "command not found"        'nosuchcmd\n'                 '' 127
check "status of last command"   'false\n'                     '' 1
check "blank lines and ;;"       '\n;;\necho ok\n'             'ok' 0
check "directory is not run"     '/usr\necho after\n'          'after' 0
check "line over 1024 bytes"     "echo $(printf 'a%.0s' {1..1100})\n" "$(printf 'a%.0s' {1..1100})" 0

# separators
check "semicolons"               'echo a; echo b ;echo c\n'    $'a\nb\nc' 0
check "&& runs on success"       'true && echo yes\n'          'yes' 0
check "|| runs on failure"       'false || echo yes\n'         'yes' 0
check "&& skips, then ; runs"    'false && echo no; echo after\n'  'after' 0
check "|| skips, then ; runs"    'true || echo no; echo after\n'   'after' 0

# exit
check "exit with status"         'exit 5\n'                    '' 5
check "exit keeps last status"   'false\nexit\n'               '' 1
check "exit illegal number"      'exit abc\n'                  '' 2

# environment
check "env"                      'env\n'                       "$BASE" 0
check "setenv then env"          'setenv T1 v1\nenv\n'         "$BASE"$'\nT1=v1' 0
check "setenv overwrites"        'setenv HOME /x\nenv\n'       $'PATH=/usr/bin:/bin\nHOME=/x\nPWD='"$CWD" 0
check "setenv exported to child" 'setenv T2 v2\nprintenv T2\n' 'v2' 0
check "setenv prefix of PATH"    'setenv PATHX /nope\nls -d /\n'   '/' 0
check "unsetenv"                 'setenv T3 x\nunsetenv T3\nenv\n' "$BASE" 0
check "env past 64 bytes"        "setenv LONG $(printf 'x%.0s' {1..80})\nprintenv LONG\nenv\n" "$(printf 'x%.0s' {1..80})"$'\n'"$BASE"$'\nLONG='"$(printf 'x%.0s' {1..80})" 0

# cd / pwd
check "cd and pwd"               'cd /\npwd\n'                 '/' 0
check "cd then external pwd"     'cd /\n/bin/pwd\n'            '/' 0
check "pwd ordering"             'cd /\npwd\n/bin/echo X\n'    $'/\nX' 0
check "cd -"                     "cd /\ncd -\n/bin/pwd\n"      "$CWD"$'\n'"$CWD" 0
check "cd with PWD unset"        'unsetenv PWD\ncd /\n/bin/pwd\n' '/' 0
check "cd with HOME unset"       'unsetenv HOME\ncd\necho alive\n' 'alive' 0

echo
echo "$pass passed, $fail failed"
[ "$fail" -eq 0 ]
