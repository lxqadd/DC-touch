


float NTC_AD[39] = {3.200765659, 3.165179419, 3.118530759, 3.058547881, 2.98534032, 2.896162368, 2.790845243, 2.666470874, 2.523673717, 2.368549401, 2.198983027, 2.01927671, 1.834521348, 1.65, 1.470597849, 1.300342971, 1.14215988, 0.997826469, 0.868093385, 0.752897908, 0.65158652, 0.563141482, 0.48635056, 0.419936324, 0.362645755, 0.313304371, 0.270456442, 0.233946049, 0.202868319, 0.1763932, 0.153795895, 0.134441279, 0.117789521, 0.103384925, 0.090245459, 0.078969993, 0.069330174, 0.061089099, 0.054041955};

float Get_PT100_tmp(float fR)
{
    float fTem;
    float fLowRValue;
    float fHighRValue;
    int   iTem;
    unsigned char i;

    //  unsigned char cLimite = 0xFF;

    unsigned char cBottom, cTop;

    if (fR > NTC_AD[0])                // 电阻值小于表格最小值，低于量程下限。
    {
        return 0xff;
    }

    if (fR < NTC_AD[38])        // 电阻值大于表格最大值，超出量程上限。
    {
        return 0xfe;
    }

    cBottom = 0;
    cTop    = 38;

    for (i = 19; (cTop - cBottom) != 1;)        // 2分法查表。
    {
        if (fR > NTC_AD[i])
        {
            cTop = i;
            i = (cTop + cBottom) / 2;
        }
        else if (fR < NTC_AD[i])
        {
            cBottom = i;
            i = (cTop + cBottom) / 2;
        }
        else
        {
            iTem = (unsigned int)i * 5 - 40;
            fTem = (float)iTem;

            return fTem;
        }
    }

    iTem = (unsigned int)i * 5 - 40;

    fLowRValue  = NTC_AD[cBottom];
    fHighRValue = NTC_AD[cTop];

    fTem = (((fLowRValue - fR) * 5) / (fLowRValue - fHighRValue)) + iTem;        // 表格是以5度为一步的。
    // 两点内插进行运算。

    return fTem;
}


