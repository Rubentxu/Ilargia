#ifndef ILARGIA_UTIL_H
#define ILARGIA_UTIL_H

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <memory>

namespace Ilargia {


    struct SDL_Deleter {
        void operator()(SDL_Surface*  ptr) { if (ptr) SDL_FreeSurface(ptr); ; ptr = nullptr;}
        void operator()(SDL_Texture*  ptr) { if (ptr) SDL_DestroyTexture(ptr); ; ptr = nullptr;}
        void operator()(Mix_Music*  ptr) { if (ptr)  Mix_FreeMusic(ptr); ptr = nullptr; }
        void operator()(Mix_Chunk*  ptr) { if (ptr)  Mix_FreeChunk(ptr); ptr = nullptr; }
        void operator()(SDL_Renderer* ptr) { if (ptr) SDL_DestroyRenderer(ptr); ; ptr = nullptr;}
        void operator()(TTF_Font*   ptr) { if (ptr) TTF_CloseFont( ptr ); ; ptr = nullptr;}
        void operator()(SDL_RWops*    ptr) { if (ptr) SDL_RWclose(ptr); ; ptr = nullptr;}
        void operator()(SDL_Window*   ptr) { if (ptr) SDL_DestroyWindow(ptr); ; ptr = nullptr;}
    };

    using SurfacePtr  = std::unique_ptr<SDL_Surface,  SDL_Deleter>;
    using TexturePtr  = std::unique_ptr<SDL_Texture,  SDL_Deleter>;
    using MusicPtr  = std::unique_ptr<Mix_Music,  SDL_Deleter>;
    using SoundFXPtr  = std::unique_ptr<Mix_Chunk,  SDL_Deleter>;
    using FontPtr  =    std::unique_ptr<TTF_Font,     SDL_Deleter>;
    using RendererPtr = std::unique_ptr<SDL_Renderer, SDL_Deleter>;
    using WindowPtr   = std::unique_ptr<SDL_Window,   SDL_Deleter>;
    using RWopsPtr    = std::unique_ptr<SDL_RWops,    SDL_Deleter>;

    using SurfaceShPtr  = shared_ptr_with_deleter<SDL_Surface,  SDL_Deleter>;
    using TextureShPtr  = shared_ptr_with_deleter<SDL_Texture,  SDL_Deleter>;
    using RendererShPtr = shared_ptr_with_deleter<SDL_Renderer, SDL_Deleter>;
    using WindowShPtr   = shared_ptr_with_deleter<SDL_Window,   SDL_Deleter>;
    using RWopsShPtr    = shared_ptr_with_deleter<SDL_RWops,    SDL_Deleter>;

}
#endif //ILARGIA_UTIL_H
