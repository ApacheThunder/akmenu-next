/*
    helpwnd.h
    Copyright (C) 2007 Acekard, www.acekard.com
    Copyright (C) 2007-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#pragma once

#include <string>
#include "dsrom.h"
#include "form.h"
#include "formdesc.h"
#include "message.h"
#include "spinbox.h"
#include "statictext.h"

class cHelpWnd : public akui::cForm {
  public:
    cHelpWnd(s32 x, s32 y, u32 w, u32 h, cWindow* parent, const std::string& text);

    ~cHelpWnd();

  public:
    void draw();

    bool process(const akui::cMessage& msg);

    cWindow& loadAppearance(const std::string& aFileName);

  protected:
    bool processKeyMessage(const akui::cKeyMessage& msg);

    void onOK();

    void onShow();

    akui::cButton _buttonOK;

    akui::cFormDesc _renderDesc;

    std::string _helpText;
};
