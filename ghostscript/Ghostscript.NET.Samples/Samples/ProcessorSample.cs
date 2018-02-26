﻿//
// ProcessorSample.cs
// This file is part of Ghostscript.NET.Samples project
//
// Author: Josip Habjan (habjan@gmail.com, http://www.linkedin.com/in/habjan) 
// Copyright (c) 2013-2014 by Josip Habjan. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
//
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

using System;
using System.Collections.Generic;
using Ghostscript.NET.Processor;

namespace Ghostscript.NET.Samples
{
    public class ProcessorSample : ISample
    {
        public void Start()
        {
            string inputFile = @"E:\gss_test\test.pdf";
            string outputFile = @"E:\gss_test\output\page-%03d.png";

            //string inputFile = @"E:\gss_test\multipage.ps";
            //string outputFile = @"E:\gss_test\output\multipage.pdf";

            int pageFrom = 1;
            int pageTo = 50;

            GhostscriptVersionInfo gv = GhostscriptVersionInfo.GetLastInstalledVersion(
                GhostscriptLicense.GPL | GhostscriptLicense.AFPL, 
                GhostscriptLicense.GPL);

            using (GhostscriptProcessor processor = new GhostscriptProcessor(gv, true))
            {
                processor.Processing += new GhostscriptProcessorProcessingEventHandler(processor_Processing);

                List<string> switches = new List<string>();
                switches.Add("-empty");
                switches.Add("-dSAFER");
                switches.Add("-dBATCH");
                switches.Add("-dNOPAUSE");
                switches.Add("-dNOPROMPT");
                switches.Add(@"-sFONTPATH=" + System.Environment.GetFolderPath(System.Environment.SpecialFolder.Fonts));
                switches.Add("-dFirstPage=" + pageFrom.ToString());
                switches.Add("-dLastPage=" + pageTo.ToString());
                switches.Add("-sDEVICE=png16m");
                switches.Add("-r96");
                switches.Add("-dTextAlphaBits=4");
                switches.Add("-dGraphicsAlphaBits=4");

                //switches.Add("-sDEVICE=pdfwrite");

                switches.Add(@"-sOutputFile=" + outputFile);
                switches.Add(@"-f");
                switches.Add(inputFile);

                processor.StartProcessing(switches.ToArray(), null);
            }
        }

        void processor_Processing(object sender, GhostscriptProcessorProcessingEventArgs e)
        {
            Console.WriteLine(e.CurrentPage.ToString() + " / " + e.CurrentPage.ToString());
        }
    }
}
