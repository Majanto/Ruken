/*
 *  MIT License
 *
 *  Copyright (c) 2019 Basile Combet, Philippe Yi
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NON INFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */

#pragma once

#include <chrono>

#include "Config.hpp"
#include "Types/FundamentalTypes.hpp"

BEGIN_DAEMON_NAMESPACE

class Clock
{
	using InternalClock = std::chrono::steady_clock;
	using TimePoint = std::chrono::time_point<InternalClock>;

	private:

		#pragma region Members

		// Last time an update has been triggered
		TimePoint m_last_update_time;

		// Number of stored ticks
		DAEuint64 m_ticks;

		// Time accumulator, this is used to later extract ticks
		DAEfloat m_accumulator;

		// Time scale of the clock, this can be used to temporarily
		// slow down or speed up the clock without having to modify the frequency of the clock
		// Be careful since this also multiplies the impressions of the clock
		DAEfloat m_time_scale;

		// Time interval between 2 ticks
		DAEfloat m_interval;

		// Is the clock paused ?
		DAEbool m_paused;

		#pragma endregion

	public:

		#pragma region Constructors

		Clock() noexcept;
		Clock(Clock const& in_copy)	 noexcept = default;
		Clock(Clock&&	   in_move)	 noexcept = default;
		~Clock()					 noexcept = default;

		#pragma endregion

		#pragma region Methods

		/**
		 * \brief Sets the frequency of the clock (number of seconds / number of ticks)
		 * \param in_interval New frequency of the clock
		 */
		DAEvoid SetFrequency(DAEfloat in_interval) noexcept;

		/**
		 * \brief Resets the clock, removing stored ticks, time accumulation and last update time
		 */
		DAEvoid Reset() noexcept;

		/**
		 * \brief Updates the clock
		 * \note The precision of the clock is update agnostic
		 */
		DAEvoid Update() noexcept;

		/**
		 * \brief Returns the status of the clock
		 * \return True if the clock is running, false otherwise
		 */
		DAEbool Status() const noexcept;

		/**
		 * \brief Pauses the clock, preventing it from generating any more ticks
		 */
		DAEvoid Pause() noexcept;

		/**
		 * \brief Unpauses the clock, resuming any previous activity
		 */
		DAEvoid Unpause() noexcept;

		/**
		 * \brief Consumes a tick if available and returns the new number of available ticks
		 * \return Number of available ticks after consumption
		 */
		DAEuint64 ConsumeTick() noexcept;

		/**
		 * \brief Returns the number of available ticks
		 * \return Number of available ticks
		 */
		DAEuint64 Ticks() const noexcept;

		/**
		 * \brief Getter/setter for the time scale property
		 * \return time scale of the clock
		 */
		DAEfloat const& TimeScale() const noexcept;
		DAEfloat&       TimeScale() noexcept;

		#pragma endregion

		#pragma region Operators

		Clock& operator=(Clock const& in_copy) noexcept = default;
		Clock& operator=(Clock&&	  in_move) noexcept = default;

		#pragma endregion
};

END_DAEMON_NAMESPACE