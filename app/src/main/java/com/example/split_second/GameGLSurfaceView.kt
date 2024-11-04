package com.example.split_second

import android.content.Context
import android.opengl.GLES20
import android.opengl.GLSurfaceView
import android.view.MotionEvent
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
            // Call native function to initialize OpenGL
            MainActivity.initOpenGL()
        }

        override fun onDrawFrame(gl: GL10) {
            // Call native function to render the frame
            MainActivity.render()
        }

        override fun onSurfaceChanged(gl: GL10, width: Int, height: Int) {
            // Set the viewport size to match the screen dimensions
            GLES20.glViewport(0, 0, width, height)
        }
    }

    override fun onTouchEvent(event: MotionEvent): Boolean {
        if (event.action == MotionEvent.ACTION_DOWN || event.action == MotionEvent.ACTION_MOVE) {
            val x = event.x
            val y = event.y
            // TODO: Pass this input to native code if needed
        }

        // Call performClick() to handle accessibility features
        performClick()

        return true
    }

    override fun performClick(): Boolean {
        super.performClick()
        // You can add any custom click behavior here if needed
        return true
    }
}