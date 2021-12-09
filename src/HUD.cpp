#include "HUD.h"

#include <SDL_ttf.h>

#include <iostream>

HUD::HUD(SDL_Renderer *sdl_renderer, PlayerController const *player1,
         PlayerController const *player2)
    : sdl_renderer_(sdl_renderer) {
  // Initialize SDL_ttf library
  TTF_Init();

  // Load fonts
  SDL_Color textColor = {255, 255, 255};
  small_ = TTF_OpenFont("../fonts/atari_vector.ttf", 12);
  if (nullptr == small_) {
    std::cerr << "True type font was not found." << std::endl;
    std::cerr << "SDL_Error: " << SDL_GetError() << std::endl;
  }
  medium_ = TTF_OpenFont("../fonts/atari_vector.ttf", 24);
  if (nullptr == medium_) {
    std::cerr << "True type font was not found." << std::endl;
    std::cerr << "SDL_Error: " << SDL_GetError() << std::endl;
  }
  large_ = TTF_OpenFont("../fonts/atari_vector.ttf", 48);
  if (nullptr == large_) {
    std::cerr << "True type font was not found." << std::endl;
    std::cerr << "SDL_Error: " << SDL_GetError() << std::endl;
  }

  // Create surface with font
  fontSurface1_ = TTF_RenderText_Solid(small_, "Player 1", textColor);
  fontSurface2_ = TTF_RenderText_Solid(medium_, "Player 1", textColor);
  fontSurface3_ = TTF_RenderText_Solid(large_, "Player 1", textColor);

  // Create font textures from surfaces
  fontTexture1_ = SDL_CreateTextureFromSurface(sdl_renderer_, fontSurface1_);
  fontTexture2_ = SDL_CreateTextureFromSurface(sdl_renderer_, fontSurface2_);
  fontTexture3_ = SDL_CreateTextureFromSurface(sdl_renderer_, fontSurface3_);

  // Set position and size of font textures
  int texH = 0;
  int texW = 0;
  SDL_QueryTexture(fontTexture1_, NULL, NULL, &texW, &texH);
  fontRect1 = {10, 10, texW, texH};

  SDL_QueryTexture(fontTexture2_, NULL, NULL, &texW, &texH);
  fontRect2 = {10, 60, texW, texH};

  SDL_QueryTexture(fontTexture3_, NULL, NULL, &texW, &texH);
  fontRect3 = {10, 120, texW, texH};
}

HUD::~HUD() {
  TTF_CloseFont(small_);
  TTF_CloseFont(medium_);
  TTF_CloseFont(large_);
  SDL_DestroyTexture(fontTexture1_);
  SDL_DestroyTexture(fontTexture2_);
  SDL_DestroyTexture(fontTexture3_);
  SDL_FreeSurface(fontSurface1_);
  SDL_FreeSurface(fontSurface2_);
  SDL_FreeSurface(fontSurface3_);
  TTF_Quit();
}

void HUD::draw() const {
  SDL_RenderCopy(sdl_renderer_, fontTexture1_, NULL, &fontRect1);
  SDL_RenderCopy(sdl_renderer_, fontTexture2_, NULL, &fontRect2);
  SDL_RenderCopy(sdl_renderer_, fontTexture3_, NULL, &fontRect3);
}