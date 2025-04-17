/*
  ==============================================================================

    ProtectYourEars.h
    Created: 16 Apr 2025 5:12:25pm
    Author:  Zachary Pennington

  ==============================================================================
*/

#pragma once
inline void protectYourEars(juce::AudioBuffer<float>& buffer)
{
    bool firstWarning = true;
    
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        
        float* channelData = buffer.getWritePointer(channel);
        
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            float x = channelData[sample];
            bool silence = false;
            
            if (std::isnan(x))
            {
                DBG("!!! WARNING: NAN DETECTED IN AUDIO BUFFER, SILENCING NOW... !!!");
                silence = true;
            }
            else if (std::isinf(x))
            {
                DBG("!!! WARNING: INFINITY DETECTED IN AUDIO BUFFER, SILENCING NOW... !!!");
                silence = true;
            }
            else if (x < -2.0f || x > 2.0f)
            {
                DBG("!!! WARNING: SAMPLE OUT OF RANGE, SILENCING NOW... !!!");
            }
            else if (x < -1.0f || x > 1.0f)
            {
                if (firstWarning)
                {
                    DBG("!!! WARNING: SAMPLE OUT OF RANGE, SILENCING NOW... !!!");
                    firstWarning = false;
                }
            }
            if (silence)
            {
                buffer.clear();
                return;
            }
            
        }
        
    }
}
