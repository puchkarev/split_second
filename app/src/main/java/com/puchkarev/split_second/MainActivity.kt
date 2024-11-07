package com.puchkarev.split_second

import android.content.res.AssetManager
import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity


class MainActivity : AppCompatActivity() {

    private lateinit var glView: GameGLSurfaceView

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        // Initialize the GLSurfaceView
        glView = GameGLSurfaceView(this)
        setContentView(glView)

        // Pass the AssetManager to the native code
        val assetManager: AssetManager = assets
        nativeSetAssetManager(assetManager)
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

        @JvmStatic
        external fun nativeSetAssetManager(assetManager: AssetManager?)
    }
}