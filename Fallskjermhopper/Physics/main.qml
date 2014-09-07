import QtQuick 2.2
import QtQuick.Window 2.1
import mycode 1.0

Window {
    visible: true
    width: 360
    height: 360

    Rectangle
    {
        id: chuteBtn

        width: 60
        height: 18
        anchors.top: parent.top
        anchors.right: parent.right
        border.color: "black"

        Text {
            id: caption
            text: qsTr("open chute")
            anchors.fill: parent
        }

        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                dragBullet.setArea(20.0);
                dragBullet.setCd(1.4);
                windBullet.setArea(20.0);
                windBullet.setCd(1.4);
            }
        }
    }

//    SimpleProjectile {
//        id: bullet

//        Component.onCompleted: bullet.initialize(
//                                   5.0, 0.0, 4000.0,        // x0, y0, z0
//                                   40.0, 0.0, 0.0,          // vx0, vy0, vz0
//                                   0.0)                     // time
//    }

    DragProjectile {
        id: dragBullet

        Component.onCompleted: dragBullet.initialize(
                                   5.0, 0.0, 4000.0,        // x0, y0, z0
                                   40.0, 0.0, 0.0,          // vx0, vy0, vz0
                                   0.0,                     // time
                                   80.0, 1.5, 1.225, 0.44)  // mass, area, density, Cd
    }

    WindProjectile {
        id: windBullet

        Component.onCompleted: windBullet.initialize(
                                   5.0, 0.0, 4000.0,        // x0, y0, z0
                                   40.0, 0.0, 0.0,          // vx0, vy0, vz0
                                   0.0,                     // time
                                   80.0, 1.5, 1.225, 0.44,  // mass, area, density, Cd
                                   -2.0, 0.0)              // windX, windY
    }



//    MouseArea {
//        anchors.fill: parent
//        onClicked: {
//            Qt.quit()
//        }
//    }

    Timer {
        interval: 100
        running: true
        repeat: true
        onTriggered: {
//            if (bullet.getZ() > 0)
//                bullet.updateLocationAndVelocity(0.5)

            if (dragBullet.getZ() > 0)
                dragBullet.updateLocationAndVelocity(0.1);

            if (windBullet.getZ() > 0)
                windBullet.updateLocationAndVelocity(0.1)
            else
                running = false

            console.log(
//                        bullet.getVelocity().toFixed(2)
//                        + "(" + bullet.getZ().toFixed(1)
//                        + ") " +
                        dragBullet.getVelocity().toFixed(2)
                        + "(" + dragBullet.getZ().toFixed(1)
                        + ") " + windBullet.getVelocity().toFixed(2)
                        + "(" + windBullet.getZ().toFixed(1) + ")")
            drawing.requestPaint()
        }
    }

    Canvas {
        id: drawing
        anchors.fill: parent

        onPaint: {
            // get context to draw with
            var ctx = getContext("2d")

            // setup the stroke
            ctx.lineWidth = 1
            ctx.fillStyle = "steelblue"

            var xScale = (0.3)
            var zScale = (360 / 4000)

            ctx.strokeStyle = "blue"
//            ctx.ellipse(bullet.getX() * xScale,
//                        -(bullet.getZ() - 4005) * zScale, 2, 2)
//            ctx.stroke()

            ctx.ellipse(dragBullet.getX() * xScale,
                        -(dragBullet.getZ() - 4005) * zScale, 2, 2)
            ctx.stroke()

            ctx.ellipse(windBullet.getX() * xScale,
                        -(windBullet.getZ() - 4005) * zScale, 2, 2)
            ctx.stroke()

            // setup the fill

            //            ctx.translate(100, 100)
            //            ctx.rotate(seconds / 30 * Math.PI)

            //            // begin a new path to draw
            //            ctx.beginPath()
            //            // top-left start point
            //            ctx.moveTo(-50, -50)
            //            // upper line
            //            ctx.lineTo(50, -50)
            //            // right line
            //            ctx.lineTo(50, 50)
            //            // bottom line
            //            ctx.lineTo(-50, 50)
            //            // left line through path closing
            //            ctx.closePath()
            //            // fill using fill style
            //            ctx.fill()
            //            // stroke using line width and stroke style
            //            ctx.stroke()

            //            ctx.rect(-2, -2, 2, 2)

            //            ctx.moveTo(0, 0)
            //            ctx.lineTo(0, -60)
            //            ctx.stroke()
        }
    }

    Text {
        text: qsTr("Hello World")
        anchors.centerIn: parent
    }
}
