#!/usr/bin/env bash

# SetCommands defined in eng\testing\tests.wasm.targets
[[SetCommands]]
[[SetCommandsEcho]]

EXECUTION_DIR=$(dirname $0)
if [[ -n "$3" ]]; then
	SCENARIO=$3
fi

export PATH=$PREPEND_PATH:$PATH

if [[ -z "$HELIX_WORKITEM_UPLOAD_ROOT" ]]; then
	XHARNESS_OUT="$EXECUTION_DIR/xharness-output"
else
	XHARNESS_OUT="$HELIX_WORKITEM_UPLOAD_ROOT/xharness-output"
fi

if [[ -n "$XHARNESS_CLI_PATH" ]]; then
	# When running in CI, we only have the .NET runtime available
	# We need to call the XHarness CLI DLL directly via dotnet exec
	HARNESS_RUNNER="dotnet exec $XHARNESS_CLI_PATH"
else
	HARNESS_RUNNER="dotnet xharness"
fi

if [[ -z "$XHARNESS_COMMAND" ]]; then
    XHARNESS_COMMAND="test"
fi

echo PATH=$PATH
echo EXECUTION_DIR=$EXECUTION_DIR
echo SCENARIO=$SCENARIO
echo XHARNESS_OUT=$XHARNESS_OUT
echo XHARNESS_CLI_PATH=$XHARNESS_CLI_PATH
echo HARNESS_RUNNER=$HARNESS_RUNNER
echo XHARNESS_COMMAND=$XHARNESS_COMMAND
echo XHARNESS_ARGS=$XHARNESS_ARGS

function _buildAOTFunc()
{
	local projectFile=$1
	local binLog=$2
	shift 2

	time dotnet msbuild $projectFile /bl:$binLog $*
	local buildExitCode=$?

	echo "\n** Performance summary for the build **\n"
	dotnet msbuild $binLog -clp:PerformanceSummary -v:q -nologo
	if [[ "$(uname -s)" == "Linux" && $buildExitCode -ne 0 ]]; then
		echo "\nLast few messages from dmesg:\n"
		local lastLines=`dmesg | tail -n 20`
		echo $lastLines

		if [[ "$lastLines" =~ "oom-kill" ]]; then
			return 9200 # OOM
		fi
	fi

	echo
	echo

    if [[ $buildExitCode -ne 0 ]]; then
        return 9100 # aot build failure
    fi

	return 0
}

pushd $EXECUTION_DIR

# ========================= BEGIN Test Execution =============================
echo ----- start $(date) ===============  To repro directly: =====================================================
echo pushd $EXECUTION_DIR
# RunCommands defined in eng\testing\tests.wasm.targets
[[RunCommandsEcho]]
echo popd
echo ===========================================================================================================
pushd $EXECUTION_DIR
# RunCommands defined in eng\testing\tests.wasm.targets
[[RunCommands]]
_exitCode=$?
popd
echo ----- end $(date) ----- exit code $_exitCode ----------------------------------------------------------

echo "XHarness artifacts: $XHARNESS_OUT"

exit $_exitCode
