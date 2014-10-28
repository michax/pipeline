// Copyright NVIDIA Corporation 2011-2012
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//  * Neither the name of NVIDIA CORPORATION nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
// OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


#include <dp/DP.h>
#include <dp/sg/renderer/rix/gl/TransparencyManagerSB.h>
#include <dp/util/File.h>
#include <GL/glew.h>

namespace dp
{
  namespace sg
  {
    namespace renderer
    {
      namespace rix
      {
        namespace gl
        {

          SmartTransparencyManagerSB TransparencyManagerSB::create()
          {
            return( std::shared_ptr<TransparencyManagerSB>( new TransparencyManagerSB() ) );
          }

          TransparencyManagerSB::TransparencyManagerSB()
            : TransparencyManager( TM_SORTED_BLENDED )
          {
          }

          TransparencyManagerSB::~TransparencyManagerSB()
          {
          }

          void TransparencyManagerSB::addFragmentCodeSnippets( bool transparent, bool depth, std::vector<std::string> & snippets )
          {
            std::string file = depth ? "emitColorDepth.glsl" : "emitColor.glsl";
            snippets.push_back( dp::util::loadStringFromFile( dp::home() + "/media/dpfx/" + file ) );
          }

          void TransparencyManagerSB::beginTransparentPass( dp::rix::core::Renderer * renderer )
          {
            TransparencyManager::beginTransparentPass( renderer );

            glDepthMask( GL_FALSE );
            glEnable( GL_BLEND );
            glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
          }

          bool TransparencyManagerSB::endTransparentPass()
          {
            glDisable( GL_BLEND );
            glDepthMask( GL_TRUE );

            return( TransparencyManager::endTransparentPass() );
          }

          void TransparencyManagerSB::initializeParameterContainer( dp::rix::core::Renderer * renderer, dp::math::Vec2ui const & viewportSize )
          {
          }

          void TransparencyManagerSB::useParameterContainer( dp::rix::core::Renderer * renderer, dp::rix::core::RenderGroupSharedHandle const & transparentRenderGroup )
          {
          }

          bool TransparencyManagerSB::needsSortedRendering() const
          {
            return( true );
          }

        } // namespace gl
      } // namespace rix
    } // namespace renderer
  } // namespace sg
} // namespace dp
