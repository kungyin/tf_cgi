#ifndef RENDERRESPONSEP2PDOWNLOADS_H
#define RENDERRESPONSEP2PDOWNLOADS_H

#include "RenderResponse.h"

class T_CONTROLLER_EXPORT RenderResponseP2pDownloads : public RenderResponse {
    Q_OBJECT

public:
    RenderResponseP2pDownloads(THttpRequest &, CGI_COMMAND);
    virtual ~RenderResponseP2pDownloads();

    virtual void preRender();

private:
    void generateP2pState();
    void generateP2pGetListByPriority();
    void generateP2pAddTorrentUrl();
    void generateP2pGetUrlState();
    void generateP2pCurrentSesState();
    void generateP2pAddTorrentFileNew();
    void generateP2pDelAllCompleted();
    void generateP2pGetTorrentScheduling();
    void generateP2pTorrentSchedulingSet();
    void generateP2pDetailTorrent();
    void generateP2pPrioritySet();
    void generateP2pDelTorrent();

};

#endif // RENDERRESPONSEP2PDOWNLOADS_H
