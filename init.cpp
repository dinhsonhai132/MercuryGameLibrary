#include <SDL3/SDL.h>
#include <iostream>

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
bool user_quit = false;

#define DLL_EXPORT __declspec(dllexport)

extern "C" {

DLL_EXPORT void init(int arr[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return;

    window = SDL_CreateWindow(
        "mergame",
        arr[0], arr[1],
        SDL_WINDOW_RESIZABLE 
    );

    if (!window) return;

    renderer = SDL_CreateRenderer(window, nullptr);
}

DLL_EXPORT void flip() {
    if (!renderer) return;

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            user_quit = true;
            exit(1);
        }
    }

    SDL_RenderPresent(renderer);
}

DLL_EXPORT void draw_square(int arr[]) {
    if (!renderer) return;

    float x = (float)arr[0];
    float y = (float)arr[1];
    float width  = (float)arr[2];
    float height = (float)arr[3];

    int r = arr[4] < 0 ? 0 : (arr[4] > 255 ? 255 : arr[4]);
    int g = arr[5] < 0 ? 0 : (arr[5] > 255 ? 255 : arr[5]);
    int b = arr[6] < 0 ? 0 : (arr[6] > 255 ? 255 : arr[6]);

    SDL_FRect rect = { x, y, width, height };

    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderFillRect(renderer, &rect);
}

DLL_EXPORT void sleep_ms(int arr[]) {
    SDL_Delay(arr[0]);
}

DLL_EXPORT void quit() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

DLL_EXPORT void fill_screen(int arr[]) {
    SDL_SetRenderDrawColor(renderer, arr[0], arr[1], arr[2], 0);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

}

int main() {
    int arr[] = {500, 400};
    int color[] = {0, 255, 0};
    init(arr);

    while (true) {
        fill_screen(color);
        flip();
    }

    return 0;
}