#pragma once

// 44100: Frecuencia de muestreo (Hz).
// MIX_DEFAULT_FORMAT: Formato de audio predeterminado.
// 2: Número de canales de audio (2 para sonido estéreo).
// 2048: Tamaño del búfer de audio. Puedes ajustar este valor según tus necesidades.

class SDLMixerInitializer {
public:
    SDLMixerInitializer();
    ~SDLMixerInitializer();
};
