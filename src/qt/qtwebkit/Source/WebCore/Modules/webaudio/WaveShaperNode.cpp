/*
 * Copyright (C) 2011, Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1.  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"

#if ENABLE(WEB_AUDIO)

#include "WaveShaperNode.h"

#include "ExceptionCode.h"
#include <wtf/MainThread.h>

namespace WebCore {

WaveShaperNode::WaveShaperNode(AudioContext* context)
    : AudioBasicProcessorNode(context, context->sampleRate())
{
    m_processor = adoptPtr(new WaveShaperProcessor(context->sampleRate(), 1));
    setNodeType(NodeTypeWaveShaper);

    initialize();
}

void WaveShaperNode::setCurve(Float32Array* curve)
{
    ASSERT(isMainThread()); 
    waveShaperProcessor()->setCurve(curve);
}

Float32Array* WaveShaperNode::curve()
{
    return waveShaperProcessor()->curve();
}

void WaveShaperNode::setOversample(const String& type, ExceptionCode& ec)
{
    ASSERT(isMainThread());

    // Synchronize with any graph changes or changes to channel configuration.
    AudioContext::AutoLocker contextLocker(context());

    if (type == "none")
        waveShaperProcessor()->setOversample(WaveShaperProcessor::OverSampleNone);
    else if (type == "2x")
        waveShaperProcessor()->setOversample(WaveShaperProcessor::OverSample2x);
    else if (type == "4x")
        waveShaperProcessor()->setOversample(WaveShaperProcessor::OverSample4x);
    else
        ec = INVALID_STATE_ERR;
}

String WaveShaperNode::oversample() const
{
    switch (const_cast<WaveShaperNode*>(this)->waveShaperProcessor()->oversample()) {
    case WaveShaperProcessor::OverSampleNone:
        return "none";
    case WaveShaperProcessor::OverSample2x:
        return "2x";
    case WaveShaperProcessor::OverSample4x:
        return "4x";
    default:
        ASSERT_NOT_REACHED();
        return "none";
    }
}

} // namespace WebCore

#endif // ENABLE(WEB_AUDIO)
