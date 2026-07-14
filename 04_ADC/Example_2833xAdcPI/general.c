float Out_Limit(float out)
{
    if (out > 1000)
        out = 1000;

    if (out < 0)
        out = 0;

    return out;
}
