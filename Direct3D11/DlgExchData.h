#pragma once
//Custom Class

/// <summary>
/// Instance, that can easily be accessed from within a dialog procedure. Used for setting and retrieving data, mainly commands.
/// </summary>
class DlgExchData
{
public:
    static DlgExchData& shared_instance() { static DlgExchData game; return game; }

    /// <summary>
    /// Number, that is contained in the most recently edited edit-control.
    /// </summary>
    FLOAT TargetVal;

    /// <summary>
    /// Currently sent IDC_Command, retrieved from a dialog procedure.
    /// </summary>
    int Val;

    /// <summary>
    /// Currently active Menu.
    /// </summary>
    int View;
private:
    DlgExchData() { Val = 0; View = 0; TargetVal = -400; }
};