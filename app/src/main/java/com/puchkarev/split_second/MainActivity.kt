package com.puchkarev.split_second

import android.content.res.AssetManager
import android.content.res.Configuration
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

        val metrics = resources.displayMetrics
        val width = metrics.widthPixels
        val height = metrics.heightPixels
        setScreenSize(width, height)
    }

    override fun onConfigurationChanged(newConfig: Configuration) {
        super.onConfigurationChanged(newConfig)
        // Update screen size when the configuration changes (e.g., rotation)
        updateScreenSize()
    }

    private fun updateScreenSize() {
        val metrics = resources.displayMetrics
        val width = metrics.widthPixels
        val height = metrics.heightPixels

        // Set screen size in native code
        setScreenSize(width, height)
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

        @JvmStatic
        external fun setScreenSize(width: Int, height: Int)
    }
}