package com.puchkarev.split_second

import android.content.Context
import android.opengl.GLES20
import android.opengl.GLSurfaceView
import android.view.MotionEvent
import com.puchkarev.split_second.MainActivity.Companion.initGame
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class GameGLSurfaceView(context: Context) : GLSurfaceView(context) {
    private val renderer: GameRenderer

    init {
        // Set OpenGL ES version (2.0)
        setEGLContextClientVersion(2)

        renderer = GameRenderer()
        setRenderer(renderer)
    }

    private class GameRenderer : Renderer {
        override fun onSurfaceCreated(gl: GL10, config: EGLConfig) {
            initGame()
        }

        override fun onDrawFrame(gl: GL10) {
            MainActivity.render()
        }

        override fun onSurfaceChanged(gl: GL10, width: Int, height: Int) {
            // Set the viewport size to match the screen dimensions
            GLES20.glViewport(0, 0, width, height)
        }
    }

    override fun onTouchEvent(event: MotionEvent): Boolean {
        if (event.action == MotionEvent.ACTION_DOWN || event.action == MotionEvent.ACTION_MOVE ||
            event.action == MotionEvent.ACTION_UP) {
            val actionType = when (event.action) {
                MotionEvent.ACTION_DOWN -> 0
                MotionEvent.ACTION_MOVE -> 1
                MotionEvent.ACTION_UP -> 2
                else -> -1
            }
            MainActivity.touchEvent(width, height, event.x, event.y, actionType)
        }
        performClick()
        return true
    }

    override fun performClick(): Boolean {
        super.performClick()
        return true
    }
}