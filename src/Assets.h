#pragma once

#include <map>
#include <string>

class Texture {};
class Animation {};
class Sound {};
class Font {};

class Assets {
  std::map<std::string, Texture> textures;
  std::map<std::string, Animation> animations;
  std::map<std::string, Sound> sounds;
  std::map<std::string, Font> fonts;

public:
  void addTexture(std::string name, std::string path);
  void addAnimation(std::string name, std::string path);
  void addSound(std::string name, std::string path);
  void addFont(std::string name, std::string path);

  Texture &getTexture(std::string name);
  Texture &getAnimation(std::string name);
  Texture &getSound(std::string name);
  Texture &getFont(std::string name);
};
