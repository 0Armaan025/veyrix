#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>

#include <SDL2/SDL_video.h>
#include <iostream>
#include <string>

using namespace std;

// im planning to put main stuff here that can be used
namespace {
constexpr int WINDOW_WIDTH = 1200;
constexpr int WINDOW_HEIGHT = 760;

// i'll change this later if it doens't go with my wallpaer
constexpr SDL_Color BACKGROOUND{20, 23, 29, 255};
constexpr SDL_Color SIDEBAR{25, 29, 37, 255};
constexpr SDL_Color PANEL{31, 36, 45, 255};
constexpr SDL_Color ACCENT{150, 180, 215, 255};
constexpr SDL_Color TEXT{232, 235, 241, 255};
constexpr SDL_Color MUTED{155, 165, 180, 255};

// some helper functions here
void fillRect(SDL_Renderer *renderer, int x, int y, int w, int h,
              SDL_Color color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_Rect rect{x, y, w, h};

  SDL_RenderFillRect(renderer, &rect);
}
// honestly, i think creating a .h file for helper functions would have been
// better, but ig i want a prototye pworking first

void drawText(SDL_Renderer *renderer, TTF_Font *font, const std::string &text,
              int x, int y, SDL_Color color) {
  if (!font) {
    return;
  }

  SDL_Surface *surface = TTF_RenderUTF8_Blended(font, text.c_str(), color);

  if (!surface) {
    return;
  }

  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

  if (texture) {
    SDL_Rect destination{

        x, y, surface->w, surface->h};

    SDL_RenderCopy(renderer, texture, nullptr, &destination);

    SDL_DestroyTexture(texture);
  }

  SDL_FreeSurface(surface);
}

} // namespace

int main() {

  // INIT

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
    cout << "SDL failed to niitalize: " << SDL_GetError() << endl;

    return 1;
  }

  if (TTF_Init() != 0) {
    cout << "Failed to initalize TTF_Font: " << TTF_GetError() << endl;

    SDL_Quit();
    return 1;
  }

  SDL_Window *window = SDL_CreateWindow(
      "Veyrix | Linux Control Center for me", SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT,
      SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

  if (!window) {
    cout << "Error: " << SDL_GetError() << endl;
    return 1;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (!renderer) {

    // I use arch and hyprland btw so for that purpose:
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
  }

  if (!renderer) {
    cout << "Error: " << SDL_GetError() << endl;
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 1;
  }

  TTF_Font *font = TTF_OpenFont("/usr/share/fonts/TTF/DejaVuSans.ttf", 16);
  TTF_Font *headingFont =
      TTF_OpenFont("/usr/share/fonts/TTF/DejaVuSans.ttf", 25);

  if (!font || !headingFont) {
    cout << "Couldn't load font: " << TTF_GetError() << endl;

    if (font)
      TTF_CloseFont(font);
    if (headingFont)
      TTF_CloseFont(headingFont);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 1;
  }

  bool running = true;
  SDL_Event event;

  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = false;
      }

      if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
        running = false;
      }
    }

    int width = 0;
    int height = 0;
    SDL_GetRendererOutputSize(renderer, &width, &height);
  }

  TTF_CloseFont(headingFont);
  TTF_CloseFont(font);

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  TTF_Quit();
  SDL_Quit();

  return 0;
}
