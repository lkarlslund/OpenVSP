//
// This file is released under the terms of the NASA Open Source Agreement (NOSA)
// version 1.3 as detailed in the LICENSE file which accompanies this software.
//

// AdvLinkVarRenameScreen.cpp: implementation of the AdvLinkVarRenameScreen class.
//
//////////////////////////////////////////////////////////////////////

#include "AdvLinkVarRenameScreen.h"
#include "AdvLinkMgr.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AdvLinkVarRenameScreen::AdvLinkVarRenameScreen( ScreenMgr* mgr ) : BasicScreen( mgr, 500, 100, "Rename Variable" )
{
    m_GenLayout.SetGroupAndScreen( m_FLTK_Window, this );

    m_GenLayout.ForceNewLine();
    m_GenLayout.AddY(5);
    m_GenLayout.AddX(5);

    m_GenLayout.AddSubGroupLayout( m_BorderLayout, m_GenLayout.GetRemainX() - 5.0,
                                   m_GenLayout.GetRemainY() - 5.0);

    m_BorderLayout.SetButtonWidth( m_BorderLayout.GetW() / 5 );
    int spaceX = m_BorderLayout.GetW() / 10;

    m_BorderLayout.AddYGap();

    m_BorderLayout.AddInput( m_VarNameInput, "Name" );

    m_BorderLayout.AddY( 25 );

    m_BorderLayout.SetSameLineFlag( true );
    m_BorderLayout.SetFitWidthFlag( false );

    m_BorderLayout.AddX( spaceX );
    m_BorderLayout.AddButton( m_OKPreserveCode, "Preserve Code" );
    m_BorderLayout.AddX( spaceX );
    m_BorderLayout.AddButton( m_OKChangeCode, "Change Code" );
    m_BorderLayout.AddX( spaceX );
    m_BorderLayout.AddButton( m_Cancel, "Cancel" );

}

AdvLinkVarRenameScreen::~AdvLinkVarRenameScreen()
{
}

bool AdvLinkVarRenameScreen::Update()
{
    BasicScreen::Update();

    Vehicle *veh = VehicleMgr.GetVehicle();

    m_FLTK_Window->redraw();

    return false;
}


void AdvLinkVarRenameScreen::Show()
{
    m_VarNameInput.Update( m_PrevName );

    m_ScreenMgr->SetUpdateFlag( true );
    BasicScreen::Show();
}

void AdvLinkVarRenameScreen::Hide()
{
    m_FLTK_Window->hide();
    m_ScreenMgr->SetUpdateFlag( true );
}

void AdvLinkVarRenameScreen::SetupAndShow( int index, const string &prevName, bool inFlag )
{
    m_InputFlag = inFlag;
    m_VarIndex = index;
    m_PrevName = prevName;

    Show();
}

void AdvLinkVarRenameScreen::CallBack( Fl_Widget* w )
{
    m_ScreenMgr->SetUpdateFlag( true );
}

void AdvLinkVarRenameScreen::GuiDeviceCallBack( GuiDevice* device )
{
    assert( m_ScreenMgr );

    if ( device == &m_OKPreserveCode )
    {
        int edit_link_index = AdvLinkMgr.GetEditLinkIndex();
        AdvLink* edit_link = AdvLinkMgr.GetLink( edit_link_index );

        if ( edit_link )
        {
            if ( m_InputFlag )
            {
                edit_link->UpdateInputVarName( m_VarIndex, m_VarNameInput.GetString(), false );
            }
            else
            {
                edit_link->UpdateOutputVarName( m_VarIndex, m_VarNameInput.GetString(), false );
            }
        }
        Hide();
    }
    else if ( device == &m_OKChangeCode )
    {
        int edit_link_index = AdvLinkMgr.GetEditLinkIndex();
        AdvLink* edit_link = AdvLinkMgr.GetLink( edit_link_index );

        if ( edit_link )
        {
            if ( m_InputFlag )
            {
                edit_link->UpdateInputVarName( m_VarIndex, m_VarNameInput.GetString(), true );
            }
            else
            {
                edit_link->UpdateOutputVarName( m_VarIndex, m_VarNameInput.GetString(), true );
            }
        }
        Hide();
    }
    else if ( device == &m_Cancel )
    {
        Hide();
    }

    m_ScreenMgr->SetUpdateFlag( true );
}
