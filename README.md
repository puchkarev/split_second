An android game about a time traveler

# Setting up the environment.

1. Install AndroidStudio [from here](https://developer.android.com/studio/install)

2. Clone the repository

```
git clone git@github.com:puchkarev/split_second
```

3. Import the submodules

```
cd split_second
git submodule init
git submodule update
```

4. Open the project located in split_second in Android Studio.
It will update/import the Gradle Files. First time this take a while.

5. It should be able to build and run.

# Game description

This is a 2d side scroller where you are traveling on a road with obstacles with some bushes oncoming cars and cars traveling the same direction.
The controls that you will have are just the ability to move left or right, and ability to drive faster or slower.
The goal is to complete as many stages as possible as quickly as possible.

When traveling closely behind another vehicle you can get a bit of a speed boost that will last for a short time.

The nuance of this specific version is that after you complete the first level, the second time around a new obstacle will be added, which is your previous
run, and this will also continue repeating for each following run. Note however since the same rules apply for all other preceding runs on the speed boost,
that means that if you end up driving in front of another (previous run) you will affect how they drive, and if that causes them to die you fail and will
have to retry this level.

# Google Play Store

The game is currently published [here](https://play.google.com/store/apps/details?id=com.puchkarev.split_second).

## Testing

### Internal Testers

To join the Internal Testers:
Follow this [link](https://play.google.com/apps/internaltest/4701096607627280823)

### Closed Testers

To join the Closed Testers:
On Android follow this [link](https://play.google.com/store/apps/details?id=com.puchkarev.split_second)
On Web follow this [link](https://play.google.com/apps/testing/com.puchkarev.split_second)

### Open Testers

To join the Open Testers:
Not yet available, since I did not complete production access requirements on Google Play Store.

Need:

* 20 closed testers
* Need to run a 14 day test with 20 testers

### Production

Don't have access yet until I complete the requirements above.

# Development

I'm open for other people participation. Just ping me.
Definitely open for game ideas, and for coding participation.

## Links

Some userful links for myself:
* [Play Console Admin Page](https://play.google.com/console/u/0/developers/8876770894052468424/app/4972653238062659679/app-dashboard?timespan=thirtyDays)

## Dependencies

Currently depend on the [stb](https://github.com/nothings/stb) project for texture loading.

## Deployment

1. Make sure all the changes are checked into github.

```git status```

should return:

```
On branch master
Your branch is up to date with 'origin/master'.

nothing to commit, working tree clean
```

2. Build and verify that the game runs on simulator.
3. Increment the version in build.gradle.kts (Module :app) versionCode and versionName
4. Build Bundle In Android Studio: Build -> Generate Signed App Bundle or APK -> Android App Bundle -> key_store_path: split_second.jks, key_alias: key0 -> release
5. Push the newly generated app/release/app-release.aab and version numbers to github from Android Studio: Git -> Commit -> Commit and Push... -> review and confirm with warnings
6. Add a release in github with the proper version number tag
7. Upload the new aab to Google Play Console and start internal testing on an android phone
8. Once internal testing looks good promote it to Closed Testing.
