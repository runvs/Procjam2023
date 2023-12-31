#include "sound_fade_info.hpp"
#include <algorithm>

jt::SoundFadeInfo::SoundFadeInfo(std::weak_ptr<jt::SoundInterface> const& sound, float duration,
    float startVolume, float endVolume)
    : m_sound(sound)
    , m_startVolume(startVolume)
    , m_endVolume(endVolume)
    , m_duration(duration)
{
}

void jt::SoundFadeInfo::update(float elapsed)
{
    m_age += elapsed;

    auto agePercent = m_age / m_duration; // 0-1
    agePercent = std::clamp(agePercent, 0.0f, 1.0f);
    auto const value = (1.0f - agePercent) * m_startVolume + agePercent * m_endVolume;

    auto const snd = m_sound.lock();
    if (snd) [[likely]] {
        snd->setVolume(value);
    }
}

bool jt::SoundFadeInfo::isAlive() const { return m_age < m_duration; }

bool jt::SoundFadeInfo::hasValidSound() const
{
    if (m_sound.expired()) {
        return false;
    }
    return true;
}
