/*
 * ParseCmd.cpp
 *
 *  Created on: 2015年3月13日
 *      Author: ian
 */

#include <cassert>
#include "ParseCmd.h"
#include "CommandDefine.h"


ParseCmd::ParseCmd(QString cmd, int group)
    : m_iCommand(CMD_NONE)
    , m_iRenderType(RENDER_TYPE_UNKNOWN)
    , m_iFilterType(COOKIE_REQ_CMDS)
{
    parse(cmd, group);
}

void ParseCmd::parse(QString cmd, int group) {

    int cgiCommandNum = sizeof(CGI_PARA_COMMANDS)/sizeof(CGI_PARA_COMMANDS[0]);
    int iSearchStart = 0;
    int iSearchEnd = cgiCommandNum;

    if(group != CMD_GRP_NONE) {
        int cgiGroupNum = sizeof(CMD_GROUP_SPACE)/sizeof(CMD_GROUP_SPACE[0]);
        for(int i = 0; i < cgiGroupNum; i++) {
            if(group == i) {
                iSearchStart = CMD_GROUP_SPACE[i][1];
                iSearchEnd = CMD_GROUP_SPACE[i][2];
                break;
            }
        }
    }


    /* 1. content of cmd to CGI_COMMAND */
    int iCmdNumber = -1;
    if( !cmd.isEmpty() ) {
        //int cgiCommandNum = sizeof(CGI_PARA_COMMANDS)/sizeof(CGI_PARA_COMMANDS[0]);
        if(cgiCommandNum == CMD_SIZE-1) {
            for(int i = iSearchStart; i < iSearchEnd; i++) {
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
        tDebug("ParseCmd::ParseCmd(): No CGI cammand is found.");


    /* 2. decide all values */
    if(iCmdNumber == -1)
        m_iCommand = CMD_NONE;
    else
        m_iCommand = findIfEqual(iCmdNumber + 1);

    bool bFound = false;
    int size = sizeof(CGI_COMMAND_TYPE_FILTER)/sizeof(CGI_COMMAND_TYPE_FILTER[0]);
    for(int i = 0; i < size; i++) {
        if(CGI_COMMAND_TYPE_FILTER[i][0] == m_iCommand) {
            m_iRenderType = CGI_COMMAND_TYPE_FILTER[i][1];
            m_iFilterType = CGI_COMMAND_TYPE_FILTER[i][2];
            bFound = true;
            break;
        }
    }

    if(!bFound) {
        tError("ParseCmd::getCGICmd(): No render type is found.");
        assert(0);
    }

}

int ParseCmd::findIfEqual(int iCmd) {

    int ret = iCmd;
    int iSize = sizeof(EQUAL_COMMANDS)/sizeof(EQUAL_COMMANDS[0]);

    for(int i = 0; i < iSize; i++) {
        if(EQUAL_COMMANDS[i][0] == iCmd) {
            ret = EQUAL_COMMANDS[i][1];
            tDebug("ParseCmd::getCGICmd(): command %d is replaced with %d", iCmd, ret);
            break;
        }
    }

    return ret;
}

