'======================================================================
' ImageMagick .NET Wrapper (VB Demo)
' is
' Copyright (C) 20Price ApS 2007,  www.20prices.com
' Free to use for non-commercial purposes
'
' NOTICE:
' ImageMagick, its logo and it source codes are
' Copyright 1999-2007 ImageMagick Studio LLC
' Please refer to http://www.imagemagick.org/script/license.php
' for details.
'=======================================================================


Public Class ConvertQuality
    Public Quality As Integer

    '----------------------------------------------------------------------
    ' Set the label to the value of the scroll bar when it changes
    '----------------------------------------------------------------------
    Private Sub HScrollBar1_ValueChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles HScrollBar1.ValueChanged
        Label2.Text = HScrollBar1.Value.ToString()
    End Sub

    '----------------------------------------------------------------------
    ' Close and return to the caller
    '----------------------------------------------------------------------
    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button1.Click
        Me.Quality = HScrollBar1.Value
        Me.Close()
    End Sub
End Class