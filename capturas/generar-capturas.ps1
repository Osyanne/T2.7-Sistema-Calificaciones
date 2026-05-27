# Genera capturas PNG estilo terminal con la salida real del programa.
# Lee los textos en UTF-8 desde capturas/textos/*.txt para evitar problemas
# de encoding en PowerShell 5.1 (que lee scripts como cp1252 si no hay BOM).
#
# Uso:  powershell -ExecutionPolicy Bypass -File generar-capturas.ps1
[CmdletBinding()]
param()

Add-Type -AssemblyName System.Drawing
$ErrorActionPreference = 'Stop'

function Render-TerminalCapture {
    param(
        [Parameter(Mandatory)] [string] $Text,
        [Parameter(Mandatory)] [string] $OutPath,
        [string] $Title = 'C:\Windows\system32\cmd.exe  -  java GestionCalificaciones'
    )

    $lines = $Text -split "`r?`n"

    $bodyFont  = New-Object System.Drawing.Font('Consolas', 14, [System.Drawing.FontStyle]::Regular)
    $titleFont = New-Object System.Drawing.Font('Segoe UI', 10, [System.Drawing.FontStyle]::Regular)

    $tempBmp = New-Object System.Drawing.Bitmap 1, 1
    $tempGfx = [System.Drawing.Graphics]::FromImage($tempBmp)
    $tempGfx.TextRenderingHint = [System.Drawing.Text.TextRenderingHint]::ClearTypeGridFit

    $maxLineWidth = 0
    foreach ($line in $lines) {
        $w = $tempGfx.MeasureString($line, $bodyFont).Width
        if ($w -gt $maxLineWidth) { $maxLineWidth = $w }
    }
    $tempGfx.Dispose()
    $tempBmp.Dispose()

    $paddingX       = 18
    $paddingY       = 14
    $titleBarHeight = 32
    $lineHeight     = 22

    $width  = [int]([math]::Ceiling($maxLineWidth + ($paddingX * 2)))
    if ($width -lt 760) { $width = 760 }
    $height = ($lines.Count * $lineHeight) + ($paddingY * 2) + $titleBarHeight

    $bmp = New-Object System.Drawing.Bitmap $width, $height
    $gfx = [System.Drawing.Graphics]::FromImage($bmp)
    $gfx.TextRenderingHint = [System.Drawing.Text.TextRenderingHint]::ClearTypeGridFit
    $gfx.SmoothingMode     = [System.Drawing.Drawing2D.SmoothingMode]::AntiAlias

    $titleBarColor  = [System.Drawing.Color]::FromArgb(48, 48, 48)
    $consoleColor   = [System.Drawing.Color]::FromArgb(12, 12, 12)
    $textColor      = [System.Drawing.Color]::FromArgb(238, 238, 238)
    $titleTextColor = [System.Drawing.Color]::FromArgb(220, 220, 220)
    $closeColor     = [System.Drawing.Color]::FromArgb(220, 60, 60)
    $minMaxColor    = [System.Drawing.Color]::FromArgb(180, 180, 180)

    $titleBrush     = New-Object System.Drawing.SolidBrush $titleBarColor
    $consoleBrush   = New-Object System.Drawing.SolidBrush $consoleColor
    $textBrush      = New-Object System.Drawing.SolidBrush $textColor
    $titleTextBrush = New-Object System.Drawing.SolidBrush $titleTextColor
    $closeBrush     = New-Object System.Drawing.SolidBrush $closeColor
    $minMaxBrush    = New-Object System.Drawing.SolidBrush $minMaxColor

    $gfx.FillRectangle($titleBrush,  0, 0, $width, $titleBarHeight)
    $gfx.FillRectangle($consoleBrush, 0, $titleBarHeight, $width, $height - $titleBarHeight)

    $gfx.DrawString($Title, $titleFont, $titleTextBrush, 12, 8)

    $btnSize = 14
    $btnY    = ($titleBarHeight - $btnSize) / 2
    $gfx.FillRectangle($closeBrush,  ($width - 24), $btnY, $btnSize, $btnSize)
    $gfx.FillRectangle($minMaxBrush, ($width - 48), $btnY, $btnSize, $btnSize)
    $gfx.FillRectangle($minMaxBrush, ($width - 72), $btnY, $btnSize, $btnSize)

    $y = $titleBarHeight + $paddingY
    foreach ($line in $lines) {
        $gfx.DrawString($line, $bodyFont, $textBrush, $paddingX, $y)
        $y += $lineHeight
    }

    $bmp.Save($OutPath, [System.Drawing.Imaging.ImageFormat]::Png)

    $gfx.Dispose()
    $bmp.Dispose()
    $titleBrush.Dispose(); $consoleBrush.Dispose(); $textBrush.Dispose()
    $titleTextBrush.Dispose(); $closeBrush.Dispose(); $minMaxBrush.Dispose()
    $bodyFont.Dispose(); $titleFont.Dispose()
}

$scriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$textosDir = Join-Path $scriptDir 'textos'

$mapa = @(
    @{ Src = '01-menu.txt';     Dst = '01-menu-y-validacion.png' },
    @{ Src = '02-registro.txt'; Dst = '02-registro.png' },
    @{ Src = '03-reporte.txt';  Dst = '03-reporte.png' },
    @{ Src = '04-busqueda.txt'; Dst = '04-busqueda.png' }
)

foreach ($item in $mapa) {
    $srcPath = Join-Path $textosDir $item.Src
    $dstPath = Join-Path $scriptDir $item.Dst
    $contenido = [System.IO.File]::ReadAllText($srcPath, [System.Text.Encoding]::UTF8)
    Render-TerminalCapture -Text $contenido -OutPath $dstPath
}

Write-Host 'Capturas generadas en' $scriptDir
Get-ChildItem -Path $scriptDir -Filter '*.png' | Format-Table Name, Length
