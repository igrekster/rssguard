// For license of this file, see <project-root-folder>/LICENSE.md.

#ifndef PLAYERBACKEND_H
#define PLAYERBACKEND_H

#include <QWidget>

class QVBoxLayout;

class PlayerBackend : public QWidget {
    Q_OBJECT

  public:
    enum class PlaybackState {
      StoppedState,
      PlayingState,
      PausedState
    };

    explicit PlayerBackend(QWidget* parent = nullptr);

    virtual QUrl url() const = 0;
    virtual int position() const = 0;
    virtual int duration() const = 0;

  signals:
    void speedChanged(int speed);
    void durationChanged(int duration);
    void positionChanged(int position);
    void errorOccurred(const QString& error_string);
    void statusChanged(const QString& status);
    void playbackStateChanged(PlaybackState state);
    void audioAvailable(bool available);
    void videoAvailable(bool available);
    void seekableChanged(bool seekable);

  public slots:
    virtual void playUrl(const QUrl& url) = 0;
    virtual void playPause() = 0;
    virtual void pause() = 0;
    virtual void stop() = 0;

    virtual void setPlaybackSpeed(int speed) = 0;
    virtual void setVolume(int volume) = 0;
    virtual void setPosition(int position) = 0;

  signals:

  private:
    QVBoxLayout* m_mainLayout;
};

#endif // PLAYERBACKEND_H
