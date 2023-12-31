﻿#ifndef JAMTEMPLATE_SOUND_HPP
#define JAMTEMPLATE_SOUND_HPP

#include <audio/sound/sound_base.hpp>
#include <audio/sound_buffer_manager/sound_buffer_manager_interface.hpp>
#include <counted_object.hpp>
#include <oalpp/sound.hpp>
#include <oalpp/sound_data.hpp>
#include <string>

namespace jt {

class Sound : public SoundBase, public CountedObj<Sound> {
public:
    Sound(std::string const& fileName, SoundBufferManagerInterface& soundManager);

    void update() override;

    float getFinalVolume() const override;

    bool isPlaying() const override;

    void play() override;
    void stop() override;
    void pause() override;

    void setPitch(float pitch) override;
    float getPitch() const override;

    void setLoop(bool doLoop) override;
    bool getLoop(void) override;

    float getDuration() const override;

    float getPosition() const override;

    int getSampleRate() const override;

private:
    std::shared_ptr<oalpp::SoundDataInterface> m_buffer;
    oalpp::Sound m_sound;
    std::string m_fileName;
};

} // namespace jt
#endif // JAMTEMPLATE_SOUND_HPP
