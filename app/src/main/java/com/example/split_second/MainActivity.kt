package com.example.split_second

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity

class MainActivity : AppCompatActivity() {

    private lateinit var glView: GameGLSurfaceView

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        // Initialize the GLSurfaceView
        glView = GameGLSurfaceView(this)
        setContentView(glView)
    }

    companion object {
        // Used to load the 'split_second' library on application startup.
        init {
            System.loadLibrary("split_second")
        }

        @JvmStatic
        external fun initGame()

        @JvmStatic
        external fun render()

        @JvmStatic
        external fun touchEvent(width: Int, height: Int, eventX: Float, eventY: Float)
    }
}