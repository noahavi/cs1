#!/bin/bash


# Sean Szumlanski
# COP 3502, Spring 2019

# ======================
# DupeyDupe: test-all.sh
# ======================
# You can run this script at the command line like so:
#
#   bash run25.sh
#
# For more details, see the assignment PDF.


################################################################################
# Shell check.
################################################################################

# Running this script with sh instead of bash can lead to false positives on the
# test cases. Yikes! These checks ensure the script is not being run through the
# Bourne shell (or any shell other than bash).

if [ "$BASH" != "/bin/bash" ]; then
  echo ""
  echo " Bloop! Please use bash to run this script, like so: bash test-all.sh"
  echo ""
  exit
fi

if [ -z "$BASH_VERSION" ]; then
  echo ""
  echo " Bloop! Please use bash to run this script, like so: bash test-all.sh"
  echo ""
  exit
fi


################################################################################
# Initialization.
################################################################################

PASS_CNT=0
NUM_TEST_CASES=23
NUM_UNIT_TESTS=2

# +2 below for the warnings and indentation checks.
TOTAL_TEST_CNT=`expr $NUM_TEST_CASES + $NUM_UNIT_TESTS + 2`


################################################################################
# Magical incantations.
################################################################################

# Ensure that obnoxious glibc errors are piped to stderr.
export LIBC_FATAL_STDERR_=1

# Now redirect all local error messages to /dev/null (like "process aborted").
exec 2> /dev/null


################################################################################
# Check that all required files are present.
################################################################################

if [ ! -f DupeyDupe.c ]; then
	echo ""
	echo " Error: You must place DupeyDupe.c in this directory before"
	echo "        we can proceed. Aborting test script."
	echo ""
	exit
elif [ ! -f DupeyDupe.h ]; then
	echo ""
	echo " Error: You must place DupeyDupe.h in this directory before"
	echo "        we can proceed. Aborting test script."
	echo ""
	exit
elif [ ! -f UnitTestLauncher.c ]; then
	echo ""
	echo " Error: You must place UnitTestLauncher.c in this directory"
	echo "        before we can proceed. Aborting test script."
	echo ""
	exit
elif [ ! -d sample_output ]; then
	echo ""
	echo " Error: You must place the sample_output folder in this directory"
	echo "        before we can proceed. Aborting test script."
	echo ""
	exit
fi

if ! [ -x "$(command -v seq)" ]; then
	echo ""
	echo " Error: seq command not found. You might see this message if"
	echo "        you're running this script on an old Mac system."
	echo "        Please be sure to test your final code on Eustis."
	echo "        Aborting test script."
	echo ""
	exit
fi

for i in `seq -f "%02g" 1 $NUM_TEST_CASES`;
do
	if [ ! -f arguments$i.txt ]; then
		echo ""
		echo " Error: You must place arguments$i.txt in this directory before we"
		echo "        can proceed. Aborting test script."
		echo ""
		exit
	fi
	if [ ! -f sample_output/arguments$i-output.txt ]; then
		echo ""
		echo " Error: You must place arguments$i-output.txt in the sample_output"
		echo "        directory before we can proceed. Aborting test script."
		echo ""
		exit
	fi
done

for i in `seq -f "%02g" 1 $NUM_UNIT_TESTS`;
do
	if [ ! -f UnitTest$i.c ]; then
		echo ""
		echo " Error: You must place UnitTest$i.c in this directory before we"
		echo "        can proceed. Aborting test script."
		echo ""
		exit
	fi
	if [ ! -f sample_output/UnitTest$i-output.txt ]; then
		echo ""
		echo " Error: You must place UnitTest$i-output.txt in the sample_output"
		echo "        directory before we can proceed. Aborting test script."
		echo ""
		exit
	fi
done

# Save a backup version of DupeyDupe.h to be restored after running this
# script, so that the #define main line ends up back how you had it.
cp DupeyDupe.h DupeyDupe_backup.h


################################################################################
# Run test cases with input specified at command line (standard test cases).
################################################################################

echo ""
echo "================================================================"
echo "Running standard test cases..."
echo "================================================================"
echo ""

# Function for running a single test case.
run_test_case()
{
	local argument_file=$1
	local output_file=$2

	echo -n "  [Test Case] $argument_file ... "

	# Ensure that DupeyDupe.h is in normal test case mode (not unit test mode).
	perl -p -i -e 's/^#define main/\/\/#define main/' DupeyDupe.h

	# Attempt to compile.
	gcc DupeyDupe.c 2> /dev/null
	compile_val=$?

	# Immediately restore header file in case the user terminates the script
	# before we can move on to the next test case.
	cp DupeyDupe_backup.h DupeyDupe.h

	# Check for compilation failure.
	if [[ $compile_val != 0 ]]; then
		echo "fail (failed to compile)"
		return
	fi

	# Run program. Capture return value to check whether it crashes.
	./a.out $(cat $argument_file) > myoutput.txt 2> /dev/null
	execution_val=$?
	if [[ $execution_val != 0 ]]; then
		echo "fail (program crashed)"
		return
	fi

	# Run diff and capture its return value.
	diff myoutput.txt sample_output/$output_file > /dev/null
	diff_val=$?
	
	# Output results based on diff's return value.
	if  [[ $diff_val != 0 ]]; then
		echo "fail (output mismatch)"
	else
		echo "PASS!"
		PASS_CNT=`expr $PASS_CNT + 1`
	fi
}

for i in `seq -f "%02g" 1 $NUM_TEST_CASES`;
do
	run_test_case "arguments$i.txt" "arguments$i-output.txt"
done


################################################################################
# Run unit tests.
################################################################################

echo ""
echo "================================================================"
echo "Running unit tests (code-based test cases)..."
echo "================================================================"
echo ""

run_unit_test()
{
	local testcase_file=$1
	local output_file=$2

	echo -n "  [Unit Case] $testcase_file ... "

	# Ensure that DupeyDupe.h is in unit test case mode.
	perl -p -i -e 's/^\/\/#define main/#define main/' DupeyDupe.h

	# Attempt to compile.
	gcc DupeyDupe.c UnitTestLauncher.c $testcase_file 2> /dev/null
	compile_val=$?

	# Immediately restore header file in case the user terminates the script
	# before we can move on to the next test case.
	cp DupeyDupe_backup.h DupeyDupe.h

	# Check for compilation failure.
	if [[ $compile_val != 0 ]]; then
		echo "fail (failed to compile)"
		return
	fi

	# Run program. Capture return value to check whether it crashes.
	./a.out > myoutput.txt 2> /dev/null
	execution_val=$?
	if [[ $execution_val != 0 ]]; then
		echo "fail (program crashed)"
		return
	fi

	# Run diff and capture its return value.
	diff myoutput.txt sample_output/$output_file > /dev/null
	diff_val=$?
	
	# Output results based on diff's return value.
	if  [[ $diff_val != 0 ]]; then
		echo "fail (output mismatch)"
	else
		echo "PASS!"
		PASS_CNT=`expr $PASS_CNT + 1`
	fi
}

for i in `seq -f "%02g" 1 $NUM_UNIT_TESTS`;
do
	run_unit_test "UnitTest$i.c" "UnitTest$i-output.txt"
done


################################################################################
# Cleanup phase.
################################################################################

# Restore header file to whatever mode it was in before running this script.
if [ -f DupeyDupe_backup.h ]; then
	mv DupeyDupe_backup.h DupeyDupe.h
fi

# Clean up the files generated by this script.
rm -f a.out
rm -f myoutput.txt


################################################################################
# Final thoughts.
################################################################################

echo ""
echo "================================================================"
echo "Final Thoughts"
echo "================================================================"
echo ""
echo "  Note: This script does not impose any runtime restrictions and"
echo "  therefore will not be able to detect any proccess timeouts"
echo "  that might be indicated in your official test case transcript."
echo ""
