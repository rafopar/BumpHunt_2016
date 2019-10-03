#include "setting_2016_pass1.h"
#include <TF1.h>

void InitVariables() {

    f_clTBotUpLim = new TF1("f_clTBotUpLim", "[0] + x*( [1] + x*[2] )", 0., 2.5);
    f_clTBotUpLim->SetParameters(57.6406, 3.40282, -1.00306);
    f_clTBotLowLim = new TF1("f_clTBotLowLim", "[0] + x*( [1] + x*[2] )", 0., 2.5);
    f_clTBotLowLim->SetParameters(47.1781, 7.55268, -1.89745);
    f_clTTopUpLim = new TF1("f_clTTopUpLim", "[0] + x*( [1] + x*[2] )", 0., 2.5);
    f_clTTopUpLim->SetParameters(58.4842, 6.33371, -3.54136);
    f_clTTopLowLim = new TF1("f_clTTopLowLim", "[0] + x*( [1] + x*[2] )", 0., 2.5);
    f_clTTopLowLim->SetParameters(49.9385, 1.38759, 0.0484333);    
}