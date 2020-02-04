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

#include "Debug/Logging/Handlers/LogHandler.hpp"

USING_DAEMON_NAMESPACE

#pragma region Public Constructors

LogHandler::LogHandler(ELogLevel const in_level) noexcept :
    m_level     { in_level },
    m_formatter { nullptr },
    m_filters   { ForwardList<LogFilter const*>() }
{
    
}

#pragma endregion

#pragma region Public Methods

DAEvoid LogHandler::CreateLock()
{

}

DAEvoid LogHandler::Acquire()
{

}

DAEvoid LogHandler::Release()
{

}

DAEvoid LogHandler::SetLevel(ELogLevel const in_level) noexcept
{
    m_level = in_level;
}

DAEvoid LogHandler::SetFormatter(LogFormatter const* in_formatter) noexcept
{
    m_formatter = in_formatter;
}

DAEvoid LogHandler::AddFilter(LogFilter const* in_filter)
{
    m_filters.push_front(in_filter);
}

DAEvoid LogHandler::RemoveFilter(LogFilter const* in_filter) noexcept
{
    m_filters.remove(in_filter);
}

DAEbool LogHandler::Filter(LogRecord const& in_record) const noexcept
{
    for (LogFilter const* filter : m_filters)
    {
        /** TODO Filtering the record. TODO*/
        if (filter)
            return false;
    }

    return true;
}

DAEvoid LogHandler::Flush()
{

}

DAEvoid LogHandler::Close()
{

}

DAEvoid LogHandler::Handle(LogRecord const& in_record)
{

}

DAEvoid LogHandler::HandleError(LogRecord const& in_record)
{

}

DAEvoid LogHandler::Format(LogRecord const& in_record)
{

}

#pragma endregion