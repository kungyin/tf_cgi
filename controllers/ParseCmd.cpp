/*
 * ParseCmd.cpp
 *
 *  Created on: 2015年3月13日
 *      Author: ian
 */

#include "ParseCmd.h"
#include "CommandDefine.h"



ParseCmd::ParseCmd(QString cmd)
    : iCmdNumber(-1)
{
    if( !cmd.isEmpty() ) {
        int cgiCommandNum = sizeof(CGI_PARA_COMMANDS)/sizeof(CGI_PARA_COMMANDS[0]);
        for(int i = 0; i < cgiCommandNum; i++) {
            QString s(CGI_PARA_COMMANDS[i]);
            if(s.compare(cmd) == 0) {
                iCmdNumber = i;
            }
        }
    }
    else {
        //cout << "No text entered for first name" << endl;
    }
}

ParseCmd::~ParseCmd() {
}

CGI_COMMAND ParseCmd::getCGICmd() {
    if(iCmdNumber == -1)
        return CMD_NONE;

    return static_cast<CGI_COMMAND>(iCmdNumber+1);
}

