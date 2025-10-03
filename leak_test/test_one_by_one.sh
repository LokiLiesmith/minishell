1.	ECHO
echo hello world
# hello world

echo -n hello
# hello   (no newline after)

echo -n -n hi
# hi      (still no newline)

echo -nnn hi
# hi      (still no newline, multiple n's allowed)

echo -nX hi
# -nX hi  (not recognized as -n option)

echo ""
# (just prints a newline)

echo
# (just prints a newline)


2. PWD
pwd
# prints current working directory (absolute path)

mkdir /tmp/testdir && cd /tmp/testdir && rmdir /tmp/testdir && pwd
# getcwd() failed: No such file or directory


3. CD
cd /tmp && pwd
# /tmp

cd
# goes to $HOME, prints nothing
pwd
# /home/echo  (or whatever $HOME is)

cd -
# prints previous directory and moves there

cd /doesnotexist
# minishell: cd: /doesnotexist: No such file or directory

unset HOME && cd
# minishell: cd: HOME not set


4.EXPORT
export TEST=hello && echo $TEST
# hello

export EMPTY= && echo $EMPTY
# (blank)

export ONLY && echo $ONLY
# (blank)

export TEST=world && echo $TEST
# world

export 1ABC=foo
# minishell: export: `1ABC=foo': not a valid identifier

export
# should print all variables in format:
# declare -x VAR="value"
# declare -x EMPTY=""
# declare -x ONLY


5.UNSET
export FOO=bar && unset FOO && echo $FOO
# (blank)

unset PATH && echo $PATH
# (blank)

export A=1 B=2 C=3 && unset B && export
# A=1 and C=3 remain

export X=1 Y=2 Z=3 && unset X Z && export
# only Y=2 remains

unset 1FOO
# minishell: unset: `1FOO': not a valid identifier


6.ENV
env
# prints all environment variables in the form:
# VAR=value
# (no declare -x, no quotes)

env nosuchcommand
# should error out:
# minishell: env: nosuchcommand: No such file or directory

7. EXIT
exit
# prints "exit" and terminates with last exit status

exit 42
# prints "exit" and terminates with status 42

exit abc
# exit
# minishell: exit: abc: numeric argument required
# terminates with status 2

exit 1 2
# exit
# minishell: exit: too many arguments
# does NOT exit, status = 1
