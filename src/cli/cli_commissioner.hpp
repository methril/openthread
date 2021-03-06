/*
 *  Copyright (c) 2019, The OpenThread Authors.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  3. Neither the name of the copyright holder nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 *   This file contains definitions for a simple CLI to control the Commissioner role.
 */

#ifndef CLI_COMMISSIONER_HPP_
#define CLI_COMMISSIONER_HPP_

#include "openthread-core-config.h"

#include <openthread/commissioner.h>

#if OPENTHREAD_CONFIG_COMMISSIONER_ENABLE && OPENTHREAD_FTD

namespace ot {
namespace Cli {

class Interpreter;

/**
 * This class implements the CLI CoAP Secure server and client.
 *
 */
class Commissioner
{
public:
    /**
     * Constructor
     *
     * @param[in]  aInterpreter  The CLI interpreter.
     *
     */
    explicit Commissioner(Interpreter &aInterpreter)
        : mInterpreter(aInterpreter)
    {
    }

    /**
     * This method interprets a list of CLI arguments.
     *
     * @param[in]  aArgsLength  The number of elements in @p aArgs.
     * @param[in]  aArgs        An array of command line arguments.
     *
     */
    otError Process(uint8_t aArgsLength, char *aArgs[]);

private:
    enum
    {
        kDefaultJoinerTimeout = 120, ///< Default timeout for Joiners, in seconds.
    };

    struct Command
    {
        const char *mName;
        otError (Commissioner::*mCommand)(uint8_t aArgsLength, char *aArgs[]);
    };

    otError ProcessHelp(uint8_t aArgsLength, char *aArgs[]);
    otError ProcessAnnounce(uint8_t aArgsLength, char *aArgs[]);
    otError ProcessEnergy(uint8_t aArgsLength, char *aArgs[]);
    otError ProcessJoiner(uint8_t aArgsLength, char *aArgs[]);
    otError ProcessMgmtGet(uint8_t aArgsLength, char *aArgs[]);
    otError ProcessMgmtSet(uint8_t aArgsLength, char *aArgs[]);
    otError ProcessPanId(uint8_t aArgsLength, char *aArgs[]);
    otError ProcessProvisioningUrl(uint8_t aArgsLength, char *aArgs[]);
    otError ProcessSessionId(uint8_t aArgsLength, char *aArgs[]);
    otError ProcessStart(uint8_t aArgsLength, char *aArgs[]);
    otError ProcessState(uint8_t aArgsLength, char *aArgs[]);
    otError ProcessStop(uint8_t aArgsLength, char *aArgs[]);

    static void HandleStateChanged(otCommissionerState aState, void *aContext);
    void        HandleStateChanged(otCommissionerState aState);

    static void HandleJoinerEvent(otCommissionerJoinerEvent aJoinerEvent,
                                  const otJoinerInfo *      aJoinerInfo,
                                  const otExtAddress *      aJoinerId,
                                  void *                    aContext);
    void        HandleJoinerEvent(otCommissionerJoinerEvent aJoinerEvent,
                                  const otJoinerInfo *      aJoinerInfo,
                                  const otExtAddress *      aJoinerId);

    static void HandleEnergyReport(uint32_t       aChannelMask,
                                   const uint8_t *aEnergyList,
                                   uint8_t        aEnergyListLength,
                                   void *         aContext);
    void        HandleEnergyReport(uint32_t aChannelMask, const uint8_t *aEnergyList, uint8_t aEnergyListLength);

    static void HandlePanIdConflict(uint16_t aPanId, uint32_t aChannelMask, void *aContext);
    void        HandlePanIdConflict(uint16_t aPanId, uint32_t aChannelMask);

    static const char *StateToString(otCommissionerState aState);

    static const Command sCommands[];
    Interpreter &        mInterpreter;
};

} // namespace Cli
} // namespace ot

#endif // OPENTHREAD_CONFIG_COMMISSIONER_ENABLE && OPENTHREAD_FTD

#endif // CLI_COMMISSIONER_HPP_
