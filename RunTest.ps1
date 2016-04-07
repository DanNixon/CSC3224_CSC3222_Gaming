<#
.SYNOPSIS
Runs a unit test case on Appveyor.
.PARAMETER TestName
Name of the test suite to run.
.EXAMPLE
RunTest -TestName Engine_Maths_Test
#>

param(
  [Parameter(Mandatory=$true)][string]$TestName
)

$platform_map=@{"Win32" = "x86"; "X64" = "x64"}
$test_platform = $platform_map.$Env:PLATFORM

vstest.console `
    /logger:Appveyor `
    /inIsolation `
    /Platform:$test_platform `
    .\bin\$TestName\$Env:PLATFORM\$Env:CONFIGURATION\$TestName.dll

if ($LASTEXITCODE -ne 0) {
  $host.SetShouldExit($LASTEXITCODE)
}
