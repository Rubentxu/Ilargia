#ifndef ILARGIA_STATEINIT_H
#define ILARGIA_STATEINIT_H

#include "GameState.h"

namespace Ilargia {

    class StateInit : public GameState {
        SDL_Texture* m_pTexture; // the new SDL_Texture variable
        SDL_Rect m_sourceRectangle; // the first rectangle
        SDL_Rect m_destinationRectangle; // another rectangle


        virtual void loadResources() {
            SDL_Surface* pTempSurface = SDL_LoadBMP("assets/rider.bmp");
            m_pTexture = SDL_CreateTextureFromSurface(_engine->getSystem<SDL_Renderer>(), pTempSurface);
            SDL_FreeSurface(pTempSurface);
        }

        virtual void init()  = 0;

        virtual void onResume() = 0;

        virtual void onPause() = 0;

        virtual void unloadResources() = 0;
    };
}



#endif //ILARGIA_STATEINIT_H
