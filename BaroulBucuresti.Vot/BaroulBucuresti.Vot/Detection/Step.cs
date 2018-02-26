using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BaroulBucuresti.Vot.Detection
{
    public enum StepType
    {
        Sharpen,
        Median,
        CannyFilter,
        SobelEdgeDetection,
        DifferenceEdgeDetection,
        BlobCounter,
        HoughLines,
        VoteCounter
    }

    public class Step
    {
        public StepType Type { get; set; }
        public dynamic Parameters { get; set; }
    }
}
