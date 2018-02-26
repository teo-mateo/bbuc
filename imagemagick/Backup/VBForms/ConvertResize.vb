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


Public Class ConvertResize

    Public imageList As ImageMagickNET.ImageList
    Public resizeWidth As Integer
    Public resizeHeight As Integer

    '----------------------------------------------------------------------
    ' Load event
    '----------------------------------------------------------------------
    Private Sub Resize_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        ' When the form is first loaded, take the current image size
        ' and fill up the textboxes with the width and height
        For Each image As ImageMagickNET.Image In imageList
            textWidth.Text = image.Columns()
            textHeight.Text = image.Rows()
            Exit For
        Next
    End Sub

    '----------------------------------------------------------------------
    ' OK Click event
    '----------------------------------------------------------------------
    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button1.Click
        ' Do some simple validation on the entered values
        '
        Try
            resizeWidth = Integer.Parse(textWidth.Text)
            resizeHeight = Integer.Parse(textHeight.Text)
        Catch ex As Exception
            MessageBox.Show("Please enter a valid width or height")
            Exit Sub
        End Try

        ' If successful, we leave the form
        '
        Me.DialogResult = Windows.Forms.DialogResult.OK
        Me.Close()

    End Sub

    '----------------------------------------------------------------------
    ' CANCEL Click event
    '----------------------------------------------------------------------
    Private Sub Button2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button2.Click
        ' Close and return
        '
        Me.DialogResult = Windows.Forms.DialogResult.Cancel
        Me.Close()
    End Sub
End Class
