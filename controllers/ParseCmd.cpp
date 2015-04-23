/*
 * ParseCmd.cpp
 *
 *  Created on: 2015年3月13日
 *      Author: ian
 */

#include <cassert>
#include "ParseCmd.h"
#include "CommandDefine.h"


ParseCmd::ParseCmd(QString cmd)
    : iCmdNumber(-1)
{
    if( !cmd.isEmpty() ) {
        int cgiCommandNum = sizeof(CGI_PARA_COMMANDS)/sizeof(CGI_PARA_COMMANDS[0]);
        if(cgiCommandNum == CMD_SIZE-1) {
            for(int i = 0; i < cgiCommandNum; i++) {
                QString s(CGI_PARA_COMMANDS[i]);
                if(s.compare(cmd) == 0) {
                    iCmdNumber = i;
                }
            }
        }
        else {
            assert(0);
            tError("ParseCmd::ParseCmd(): The number of CGI strings is %d, but enum command size is %d."
                   , cgiCommandNum, CMD_SIZE);
        }
    }
    else
        tError("ParseCmd::ParseCmd(): No CGI cammand is found.");
}

CGI_COMMAND ParseCmd::getCGICmd() {
    if(iCmdNumber == -1)
        return CMD_NONE;

    return static_cast<CGI_COMMAND>(iCmdNumber+1);
}

