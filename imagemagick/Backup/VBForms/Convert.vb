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


Imports ImageMagickNET
Imports System.IO

Public Class Convert

    Public imageList As ImageMagickNET.ImageList = New ImageMagickNET.ImageList()
    Private files() As String
    Private idx As Integer

    Private Sub Label1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs)
    End Sub

    '----------------------------------------------------------------------
    ' Load file from the path specified.
    '----------------------------------------------------------------------
    Private Sub LoadFile(ByVal filename As String)
        ' we load all formats as a list of images 
        ' (single frame images such as JPG will only contain one image in the list)
        imageList = New ImageMagickNET.ImageList()
        imageList.ReadImages(filename)
        Me.Text = filename

        ' Once the file is loaded, refresh the picturebox to show the image
        PictureBox1.Refresh()
    End Sub

    '----------------------------------------------------------------------
    ' Save file from the path specified.
    '----------------------------------------------------------------------
    Private Sub SaveFile(ByVal filename As String)
        ' write all images into a single file
        ' 
        ' Notice that we pass in true as the second parameter
        ' to indicate that we want an adjoin file, ie, all frames
        ' in one file.
        '
        ' If we pass in false, each frame will be saved as a separate
        ' as according to the Magick++ documentation.
        '
        imageList.WriteImages(filename, True)
    End Sub

    '----------------------------------------------------------------------
    ' Set the compression quality of the image.
    '----------------------------------------------------------------------
    Private Sub SetQuality()
        ' set quality for all images in the list
        ' but normally set quality only applies to JPG or 
        ' coders that use the quality property.
        For Each image As ImageMagickNET.Image In imageList
			image.Quality = ConvertQuality.Quality
        Next
    End Sub


    '----------------------------------------------------------------------
    ' Open the file dialog and load an image.
    '----------------------------------------------------------------------
    Private Sub LoadToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles LoadToolStripMenuItem.Click
        ' Open the open file dialog
        If OpenFileDialog1.ShowDialog() = Windows.Forms.DialogResult.OK Then
            ' If the user clicks OK, then load up the file
            LoadFile(OpenFileDialog1.FileName)

            ' Get all files in the folder
            ' so that the user can cycle through them easily
            '
            files = Directory.GetFiles(Path.GetDirectoryName(OpenFileDialog1.FileName), "*.*")

            ' Set the filename for the Save dialog, so that the user
            ' can choose to save it back to the same file name.
            SaveFileDialog1.FileName = Path.GetFileNameWithoutExtension(OpenFileDialog1.FileName)
        End If
    End Sub

    '----------------------------------------------------------------------
    ' Open the Save file dialog and save the image.
    '----------------------------------------------------------------------
    Private Sub SaveToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles SaveToolStripMenuItem.Click
        ' Open the save file dialog
        If SaveFileDialog1.ShowDialog() = Windows.Forms.DialogResult.OK Then
            ' clear the file name's extension from the SaveFile dialog
            SaveFileDialog1.FileName = Path.GetFileNameWithoutExtension(SaveFileDialog1.FileName)

            ' If the user clicks OK, we do a check to see if the file
            ' format is a JPG. If so, show the compression quality dialog
            '
            If (SaveFileDialog1.FileName.ToUpper().EndsWith(".JPG")) Then
                ConvertQuality.ShowDialog()
                SetQuality()
            End If

            ' We save the file
            SaveFile(SaveFileDialog1.FileName)
        End If
    End Sub

    '----------------------------------------------------------------------
    ' Resize menu
    '----------------------------------------------------------------------
    Private Sub ResizeToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ResizeToolStripMenuItem.Click
        ' this dialog box helps to resize the images in the list
        '
        ConvertResize.imageList = Me.imageList
        ConvertResize.ShowDialog()

        ' Once the user has entered the new size, we do a resize on all
        ' the images.
        Dim percentage As Double = 0
        Dim firstImage As Boolean = True
        Dim oldwidth As Integer = 0, oldheight As Integer = 0

        For Each image As ImageMagickNET.Image In imageList
            If firstImage = True Then
                ' For the first image, we do a resize according to the size
                ' specified by the user
                '
                firstImage = False

				oldwidth = image.Columns
                image.Resize(New ImageMagickNET.Geometry( _
                  ConvertResize.resizeWidth, ConvertResize.resizeHeight, _
                    0, 0, False, False))
                percentage = CDbl(image.Columns()) / oldwidth

            Else
                ' however, for subsequent images, we do a resize based on the
                ' resize percentage of the first image to be consistent.
                '
				image.Resize(New ImageMagickNET.Geometry( _
				  percentage * image.Columns, _
				  percentage * image.Rows, 0, 0, False, False))
            End If
        Next

        ' Once the resize is complete, do a refresh to paint the image
        ' on the screen
        '
        PictureBox1.Refresh()
    End Sub

    '----------------------------------------------------------------------
    ' Resize form
    '----------------------------------------------------------------------
    Private Sub MenuStrip1_Resize(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MenuStrip1.Resize
        PictureBox1.Height = Me.ClientSize.Height - MenuStrip1.Height
        PictureBox1.Width = Me.ClientSize.Width
    End Sub

    '----------------------------------------------------------------------
    ' PictureBox1 Paint event
    '----------------------------------------------------------------------
    Private Sub PictureBox1_Paint(ByVal sender As System.Object, ByVal e As System.Windows.Forms.PaintEventArgs) Handles PictureBox1.Paint
        ' just draw the first image (regardless of how many there are in the list)
        ' of course, it would be trivial to show animated GIF by cycling through
        ' all images in the list, via a timer.
        '
        For Each image As ImageMagickNET.Image In imageList
            If image.Columns > PictureBox1.Width Or image.Rows > PictureBox1.Height Then
                PictureBox1.SizeMode = PictureBoxSizeMode.Zoom
            Else
                PictureBox1.SizeMode = PictureBoxSizeMode.CenterImage
            End If

            ' This is where we can attach the .NET Bitmap constructed from the image
            ' to our PictureBoxn
            PictureBox1.Image = image.ToBitmap
            Exit For
        Next

    End Sub

    '----------------------------------------------------------------------
    ' Load event
    '----------------------------------------------------------------------
    Private Sub Convert_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        ' initialize the ImageMagick library here
        MagickNet.InitializeMagick(Application.ExecutablePath)
    End Sub


    '----------------------------------------------------------------------
    ' Keydown event
    '----------------------------------------------------------------------
    Private Sub Convert_KeyDown(ByVal sender As System.Object, ByVal e As System.Windows.Forms.KeyEventArgs) Handles MyBase.KeyDown

        If e.KeyCode = Keys.PageDown Or e.KeyCode = Keys.PageUp Then
            While True
                Select Case e.KeyCode
                    Case Keys.PageDown
                        idx += 1
                        If idx = files.Length Then idx = 0
                    Case Keys.PageUp
                        idx -= 1
                        If idx < 0 Then idx = files.Length - 1
                End Select
                Try
                    LoadFile(files(idx))
                    Exit While
                Catch
                End Try
            End While
        End If
    End Sub
End Class
