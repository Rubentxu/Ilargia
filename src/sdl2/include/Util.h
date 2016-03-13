#ifndef ILARGIA_UTIL_H
#define ILARGIA_UTIL_H

#include <SDL.h>
#include <memory>

namespace Ilargia {

    struct SDL_Deleter {
        void operator()(SDL_Surface*  ptr) { if (ptr) SDL_FreeSurface(ptr); }
        void operator()(SDL_Texture*  ptr) { if (ptr) SDL_DestroyTexture(ptr); }
        void operator()(SDL_Renderer* ptr) { if (ptr) SDL_DestroyRenderer(ptr); }
        void operator()(SDL_Window*   ptr) { if (ptr) SDL_DestroyWindow(ptr); }
        void operator()(SDL_RWops*    ptr) { if (ptr) SDL_RWclose(ptr); }
    };

    using SurfacePtr  = std::unique_ptr<SDL_Surface,  SDL_Deleter>;
    using TexturePtr  = std::unique_ptr<SDL_Texture,  SDL_Deleter>;
    using RendererPtr = std::unique_ptr<SDL_Renderer, SDL_Deleter>;
    using WindowPtr   = std::unique_ptr<SDL_Window,   SDL_Deleter>;
    using RWopsPtr    = std::unique_ptr<SDL_RWops,    SDL_Deleter>;
}
#endif //ILARGIA_UTIL_H
