param (
    [Parameter(Mandatory = $true)]
    [string]$Path
)

# Load limits
$limits = Get-Content "$Path\limits.yaml"
$timeLimit = ($limits | Where-Object { $_ -match 'time_limit' }) -replace '.*time_limit:\s*', ''
$memoryLimit = ($limits | Where-Object { $_ -match 'memory_limit' }) -replace '.*memory_limit:\s*', ''

# Verdict priority
$verdictPriority = @{
    "COMPILATION ERROR" = 4
    "RUNTIME ERROR" = 3
    "TIME/MEMORY LIMIT EXCEEDED" = 2
    "WRONG ANSWER" = 1
    "ACCEPTED" = 0
}

$finalResults = @()

Get-ChildItem "$Path\submission" -Filter *.cpp | ForEach-Object {
    $name = $_.BaseName
    $source = $_.FullName
    $executable = "$name.exe"

    Write-Host "Judging $name..."

    & g++ -std=c++17 "$source" -o "$executable" 2> "$name.compile.log"
    if ($LASTEXITCODE -ne 0) {
        Write-Host "$name`: COMPILATION ERROR" -ForegroundColor Red
        $finalResults += "$name`: COMPILATION ERROR"
        continue
    }

    $highestVerdict = "ACCEPTED"
    $inputs = Get-ChildItem "$Path\input" -Filter "input*.txt" | Sort-Object Name

    foreach ($inFile in $inputs) {
        $caseId = ($inFile.BaseName -replace 'input', '')
        $ansFile = "$Path\answer\answer$caseId.txt"
        $outputFile = "output_file.txt"

        # Add sentinel line to input file to detect infinite loops
        $inputWithSentinel = "input_with_sentinel.txt"
        Get-Content $inFile.FullName | Set-Content $inputWithSentinel
        Add-Content $inputWithSentinel "`n$([System.Random]::new().Next())"

        # Run the program and wait with timeout
        $p = Start-Process -FilePath ".\$executable" -RedirectStandardInput $inputWithSentinel `
            -RedirectStandardOutput $outputFile -NoNewWindow -PassThru

        $finished = $p.WaitForExit([int]$timeLimit * 1000)

        if (-not $finished) {
            $p.Kill()
            $testVerdict = "TIME/MEMORY LIMIT EXCEEDED"
        } elseif ($p.ExitCode -eq 124 -or $p.ExitCode -eq 137) {
            $testVerdict = "TIME/MEMORY LIMIT EXCEEDED"
        } elseif ($p.ExitCode -ne 0) {
            $testVerdict = "RUNTIME ERROR"
        } else {
            # Normalize output and answer by trimming and removing empty lines
            $ansText = (Get-Content $ansFile | Where-Object { $_.Trim() -ne "" } | ForEach-Object { $_.Trim() }) -join "`n"
            $outText = (Get-Content $outputFile | Where-Object { $_.Trim() -ne "" } | ForEach-Object { $_.Trim() }) -join "`n"
            if ($ansText -ne $outText) {
                $testVerdict = "WRONG ANSWER"
            } else {
                $testVerdict = "ACCEPTED"
            }
        }

        $color = if ($testVerdict -eq "ACCEPTED") { "Green" } else { "Red" }
        Write-Host "Test $caseId`: $testVerdict" -ForegroundColor $color

        if ($verdictPriority[$testVerdict] -gt $verdictPriority[$highestVerdict]) {
            $highestVerdict = $testVerdict
        }
    }

    $colorFinal = if ($highestVerdict -eq "ACCEPTED") { "Green" } else { "Red" }
    Write-Host "$name`: $highestVerdict" -ForegroundColor $colorFinal
    $finalResults += "$name`: $highestVerdict"

    Remove-Item $executable, $outputFile, "$name.compile.log", $inputWithSentinel -ErrorAction Ignore
}

Write-Host "`n================== FINAL VERDICTS ==================" -ForegroundColor Yellow
$finalResults | ForEach-Object { Write-Host $_ }
