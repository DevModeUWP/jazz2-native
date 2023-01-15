#pragma once

#include "../Base/Object.h"

#include <Containers/StringView.h>

using namespace Death::Containers;

namespace nCine
{
	class IAudioLoader;

	/// A class representing an OpenAL buffer
	/*! It inherits from `Object` because a buffer can be
	 *  shared by more than one `AudioBufferPlayer` object. */
	class AudioBuffer : public Object
	{
	public:
		enum class Format
		{
			MONO8,
			STEREO8,
			MONO16,
			STEREO16
		};

		/// Creates an OpenAL buffer name
		AudioBuffer();
		/// A constructor creating a buffer from memory
		AudioBuffer(const unsigned char* bufferPtr, unsigned long int bufferSize);
		/// A constructor creating a buffer from a file
		explicit AudioBuffer(const StringView& filename);
		~AudioBuffer() override;

		/// Move constructor
		AudioBuffer(AudioBuffer&& other);
		/// Move assignment operator
		AudioBuffer& operator=(AudioBuffer&& other);

		/// Initializes an empty buffer with the specified format and frequency
		void init(Format format, int frequency);

		bool loadFromMemory(const unsigned char* bufferPtr, unsigned long int bufferSize);
		bool loadFromFile(const StringView& filename);
		/// Loads samples in raw PCM format from a memory buffer
		bool loadFromSamples(const unsigned char* bufferPtr, unsigned long int bufferSize);

		/// Returns the OpenAL buffer id
		inline unsigned int bufferId() const {
			return bufferId_;
		}

		/// Returns the number of bytes per sample
		inline int bytesPerSample() const {
			return bytesPerSample_;
		}
		/// Returns the number of audio channels
		inline int numChannels() const {
			return numChannels_;
		}
		/// Returns the samples frequency
		inline int frequency() const {
			return frequency_;
		}

		/// Returns number of samples
		inline unsigned long int numSamples() const {
			return numSamples_;
		}
		/// Returns the duration in seconds
		inline float duration() const {
			return duration_;
		}

		/// Returns the size of the buffer in bytes
		inline unsigned long bufferSize() const {
			return numSamples_ * numChannels_ * bytesPerSample_;
		}

		inline static ObjectType sType() {
			return ObjectType::AudioBuffer;
		}

	private:
		/// The OpenAL buffer id
		unsigned int bufferId_;

		/// Number of bytes per sample
		int bytesPerSample_;
		/// Number of channels
		int numChannels_;
		/// Samples frequency
		int frequency_;

		/// Number of samples
		unsigned long int numSamples_;
		/// Duration in seconds
		float duration_;

		/// Loads audio samples based on information from the audio loader and reader
		bool load(IAudioLoader& audioLoader);

		/// Deleted copy constructor
		AudioBuffer(const AudioBuffer&) = delete;
		/// Deleted assignment operator
		AudioBuffer& operator=(const AudioBuffer&) = delete;
	};
}
