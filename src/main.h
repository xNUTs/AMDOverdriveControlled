/*******************************************************************************

 * This program reads HW information from your ATI Radeon card and displays them
 * You can also change frequencies and voltages.

 * THIS PROGRAM MAY DAMAGE YOUR VIDEO CARD, IF YOU APPLY NONSENSIAL VALUES.
 * e.g. INCREASING THE VOLTAGES AND FREQUENCIES IN CONJUNCTION WITH LOWERING THE
 *      FAN SPEED IS NOT ADVISABLE!

 * Copyright(C) Thorsten Gilling (tgilling@web.de)

 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*******************************************************************************/

// TODO - Code review
// TODO - !!! TESTING !!!

#ifndef __main__
#define __main__

// main wxWidgets header file
#include <wx/wx.h>
#include <wx/cmdline.h>

// gui classes generated by wxFormBuilder
#include "gui.h"

#include "CMonitorPanel.h"
#include "CInfoPanel.h"
#include "CFanSpeedPanel.h"
#include "CAuthorPanel.h"
#include "CFanControlPanel.h"
#include "CAppProfilePanel.h"
#include "COvdrSettingsPanel.h"
#include "CTaskBarIcon.h"
#include "CColorTempPanel.h"

////////////////////////////////////////////////////////////////////////////////
// application class declaration
////////////////////////////////////////////////////////////////////////////////
static const wxCmdLineEntryDesc g_cmdLineDesc [] =
{
     { wxCMD_LINE_SWITCH, wxT("h"), wxT("help"), wxT("displays help on the command line parameters"),
       wxCMD_LINE_VAL_NONE, wxCMD_LINE_OPTION_HELP },

     { wxCMD_LINE_PARAM, wxT(""), wxT(""), wxT("profile name"),
       wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL },

     { wxCMD_LINE_SWITCH, wxT("b"), wxT("batch-mode"), wxT("only set profile, no GUI"),
       wxCMD_LINE_VAL_NONE, wxCMD_LINE_PARAM_OPTIONAL },

     { wxCMD_LINE_SWITCH, wxT("a"), wxT("enable-app-profiles"), wxT("set color temperature"),
       wxCMD_LINE_VAL_NONE, wxCMD_LINE_PARAM_OPTIONAL },

     { wxCMD_LINE_OPTION, wxT("c"), wxT("color-temp"), wxT("set color temperature"),
       wxCMD_LINE_VAL_NUMBER, wxCMD_LINE_PARAM_OPTIONAL },

     { wxCMD_LINE_NONE, wxT(""), wxT(""), wxT(""), wxCMD_LINE_VAL_NONE, wxCMD_LINE_PARAM_OPTIONAL }
};

class MainApp : public wxApp
{
    public:
        virtual bool OnInit();
	virtual void OnInitCmdLine(wxCmdLineParser& parser);
	virtual bool OnCmdLineParsed(wxCmdLineParser& parser);

    protected:
	bool mBatchMode;
	wxString mProfileName;
	bool mEnableAppProfiles;
	long int mColorTemp;
	bool mSetColorTemp;
};

// declare global static function wxGetApp()
DECLARE_APP(MainApp)

////////////////////////////////////////////////////////////////////////////////
// main application frame declaration
////////////////////////////////////////////////////////////////////////////////

class MainDialog : public MainDialogBase, wxTimer
{
    public:
        MainDialog(wxWindow *parent);
        virtual ~MainDialog();

        bool LoadXML(wxString filename);
        bool SaveXML(wxString filename);

        void EnableAppProfiles();
	void SetColorTemperature(int color_temp);

        void SetStartupProfileName(const wxString& mStartupProfileName) {this->mStartupProfileName = mStartupProfileName;}

    protected:
        // protected event handlers
        virtual void OnCloseDialog(wxCloseEvent& event);
        virtual void OnOKClick(wxCommandEvent& event);
        virtual void OnInit(wxInitDialogEvent& event);
        virtual void OnNotebookPageChanged(wxNotebookEvent& event);
        virtual void mLoadButtonClick(wxCommandEvent& event);
        virtual void mSaveButtonClick(wxCommandEvent& event);
        virtual void mExitButtonClick(wxCommandEvent& event);

        wxString mStartupProfileName;

        bool mMustAddPages;

        CInfoPanel* mpInfoPanel;
        CFanSpeedPanel* mpFanSpeedPanel;
        CAuthorPanel* mpAuthorPanel;
        CMonitorPanel* mpMonitorPanel;
        CFanControlPanel* mpFanControlPanel;
        CAppProfilePanel* mpAppProfilePanel;
        COvdrSettingsPanel* mpOvdrSettingsPanel;
	CColorTempPanel* mpColorTempPanel;

        CTaskBarIcon* mpTaskBarIcon;

        void Notify();

        bool IsAppRunning(wxString app);
};

#endif //__main__
