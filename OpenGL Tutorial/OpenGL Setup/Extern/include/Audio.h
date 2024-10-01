/******************************************************************************/
/*!
\par        Project: Amu Engine
\file       Audio.h

\author     Shinwoo Choi
\date       Oct 30, 2024

\brief      Header file for the library settings.
*/
/******************************************************************************/
#ifndef AUDIO_H
#define AUDIO_H


#include "Export.h"
#include "Type.h"

typedef struct Audio {
    struct FMOD_SOUND* fmod_sound; ///< internal FMOD variable. DO NOT TOUCH.
} Audio;

typedef struct AudioGroup {
    struct FMOD_CHANNELGROUP* fmod_group; ///< internal FMOD variable. DO NOT TOUCH.
} AudioGroup;


#ifdef __cplusplus
extern "C"
{
#endif


    /******************************************************************************/
    /*!
    \fn         int AudioInit (void)

    \brief      Initializes the Audio module.

    \details    Already called in SysInit, so users shouldn't need to call this.

    \retval     int
                Return 1 if initialization is successful.
                Else return 0.
    */
    /******************************************************************************/
    API int AudioInit(void);

    /******************************************************************************/
    /*!
    \fn         void AudioUpdate()

    \brief      Updates the Audio module.

    \warning    Already called in SysFrameStart, so users shouldn't need to call this.

    */
    /******************************************************************************/
    API void AudioUpdate(void);

    /******************************************************************************/
    /*!
    \fn         int AudioExit(void)

    \brief      Cleans up resources used by the the Audio module.

    \warning    Already called in SysExit, so users shouldn't need to call this.

    */
    /******************************************************************************/
    API void AudioExit(void);

    /******************************************************************************/
    /*!
    \fn         int AudioIsValidAudio(Audio audio)

    \brief      Checks if the Audio given is valid

    \retval     int
                    Returns 0 if invalid, 1 otherwise.
    */
    /******************************************************************************/
    API int AudioIsValidAudio(Audio audio);

    /******************************************************************************/
    /*!
    \fn         int AudioIsValidGroup(AudioGroup group)

    \brief      Checks if the AudioGroup given is valid

    \param      [in] group
                The audio group to check the validity of.

    \retval     int
                    Returns 0 if invalid, 1 otherwise.
    */
    /******************************************************************************/
    API int AudioIsValidGroup(AudioGroup group);

    /******************************************************************************/
    /*!
    \fn         AudioGroup AudioCreateGroup(void)

    \brief      Create an audio group for audio to be played on.

    \retval     AudioGroup
                Returns a handle to AudioGroup which represents an audio group.
                Use AudioIsValidGroup() to check if it's valid.
    */
    /******************************************************************************/
    API AudioGroup AudioCreateGroup(void);

    /******************************************************************************/
    /*!
    \fn         Audio AudioLoadSound(const char* filepath)

    \brief      Creates an audio that represents a sound to be played.

    \param      [in] filepath
                The file path of the sound to load.

    \warning    You should use this for short sounds, typically sound effects.

    \retval     Audio
                Returns a handle to Audio which represents an audio that can be played.
                Use AudioIsValidAudio() to check if it's valid.
    */
    /******************************************************************************/
    API Audio AudioLoadSound(const char* filepath);

    /******************************************************************************/
    /*!
    \fn         Audio AudioLoadMusic(const char* filepath)

    \brief      Creates an audio that represents a music to be played.

    \param      [in] filepath
                The file path of the music to load.

    \warning    You should use this for long sounds, typically background music.

    \retval     Audio
                Returns a handle to Audio which represents an audio that can be played.
                Use AudioIsValidAudio() to check if it's valid.
    */
    /******************************************************************************/
    API Audio AudioLoadMusic(const char* filepath);

    /******************************************************************************/
    /*!
    \fn         void AudioPlay(Audio audio, AudioGroup group, float volume, float pitch, int loops)

    \brief      Plays an audio.

    \param      [in] audio
                The audio to play.

    \param      [in] group
                The audio group to play the audio on.

    \param      [in] volume
                The volume of the audio to play.
                The range is from 0 to 1, where 0 represents 0% and 1 represents 100%

    \param      [in] pitch
                The pitch of the audio to play.
                The range is from 0 to 1, where 0 represents 0% and 1 represents 100%

    \param      [in] loops
                The amount of time to loop the audio.
                0 means that the audio will play once.
                1 means that the audio will play twice.
                -1 means that the audio will loop forever.

    */
    /******************************************************************************/
    API void AudioPlay(Audio audio, AudioGroup group, float volume, float pitch, int loops);

    /******************************************************************************/
    /*!
    \fn         void AudioResumeGroup(AudioGroup group)

    \brief      Resumes the audios in an audio group.

    \param      [in] group
                The audio group to resume.

    */
    /******************************************************************************/
    API void AudioResumeGroup(AudioGroup group);

    /******************************************************************************/
    /*!
    \fn         void AudioStopGroup(AudioGroup group)

    \brief      Stops the audios in an audio group.

    \param      [in] group
                The audio group to stop.

    */
    /******************************************************************************/
    API void AudioStopGroup(AudioGroup group);

    /******************************************************************************/
    /*!
    \fn         void AudioPauseGroup(AudioGroup group)

    \brief      Pauses the audios in an audio group.

    \param      [in] group
                The audio group to pause.

    */
    /******************************************************************************/
    API void AudioPauseGroup(AudioGroup group);

    /******************************************************************************/
    /*!
    \fn         void AudioSetGroupVolume(AudioGroup group, float volume)

    \brief      Changes the volume of the audio group.

    \param      [in] group
                The audio group to change the volume of.

    \param      [in] volume
                The volume of the audio group.
                The range is from 0 to 1, where 0 represents 0% and 1 represents 100%

    */
    /******************************************************************************/
    API void AudioSetGroupVolume(AudioGroup group, float volume);

    /******************************************************************************/
    /*!
    \fn         void AudioSetGroupPitch(AudioGroup group, float pitch)

    \brief      Changes the pitch of the audio group.

    \param      [in] group
                The audio group to change the pitch of.

    \param      [in] pitch
                The pitch of the audio group.
                The range is from 0 to 1, where 0 represents 0% and 1 represents 100%

    */
    /******************************************************************************/
    API void AudioSetGroupPitch(AudioGroup group, float pitch);

    /******************************************************************************/
    /*!
    \fn         Audio AudioUnloadAudio(Audio audio)

    \brief      Unloads resources allocated for an audio.

    \param      [in] audio
                The audio to unload.

    */
    /******************************************************************************/
    API void AudioUnloadAudio(Audio audio);

    /******************************************************************************/
    /*!
    \fn         Audio AudioUnloadAudioGroup(AudioGroup group)

    \brief      Unloads resources allocated for an audio group.

    \param      [in] group
                The audio group to unload.
    */
    /******************************************************************************/
    API void AudioUnloadAudioGroup(AudioGroup group);

#ifdef __cplusplus
}
#endif

#endif // AUDIO_H
