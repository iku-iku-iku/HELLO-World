//
// Created by iku-iku-iku on 2022/10/3.
//


#pragma once

#include <Lib/Math.h>
#include "glm/gtc/matrix_transform.hpp"

namespace core {
    struct Matrix4f {
        Matrix4f() = default;

        Matrix4f(const glm::mat4 &mat) : Mat(mat) {}

        operator glm::mat4 &() { return Mat; }

        operator const glm::mat4 &() const { return Mat; }

        Matrix4f operator*(const Matrix4f &rhs) const { return Mat * rhs.Mat; }

        glm::vec4 operator*(const glm::vec4 &rhs) const { return Mat * rhs; }

        Matrix4f T() const { return glm::transpose(Mat); }

        glm::mat4 &Get() const { return Mat; }

    protected:
        mutable glm::mat4 Mat{};
    };

    struct Rotation {
        mutable Matrix4f Mat;
        /// type support

        Rotation(const glm::mat4 &mat) : Mat(mat) {}

        Rotation(const Matrix4f &mat) : Mat(mat) {}

        static Matrix4f PitchMat(float rad) {
            return glm::rotate(glm::mat4(1.f), rad, glm::vec3(1.f, 0.f, 0.f));
        }

        static Matrix4f YawMat(float rad) {
            return glm::rotate(glm::mat4(1.f), rad, glm::vec3(0.f, 1.f, 0.f));
        }

        static Matrix4f RollMat(float rad) {
            return glm::rotate(glm::mat4(1.f), rad, glm::vec3(0.f, 0.f, 1.f));
        }

        static Rotation PitchRot(float rad) {
            return glm::rotate(glm::mat4(1.f), rad, glm::vec3(1.f, 0.f, 0.f));
        }

        static Rotation YawRot(float rad) {
            return glm::rotate(glm::mat4(1.f), rad, glm::vec3(0.f, 1.f, 0.f));
        }

        static Rotation RollRot(float rad) {
            return glm::rotate(glm::mat4(1.f), rad, glm::vec3(0.f, 0.f, 1.f));
        }


        /// rotation support

        Rotation(float p, float y, float r) : Pitch(p), Yaw(y), Roll(r),
                                              PitchDirty(1), YawDirty(1), RollDirty(1),
                                              InvDirty(1), MatDirty(1),
                                              PMat(PitchMat(p)), YMat(YawMat(y)), RMat(RollMat(r)) {
        }

        Rotation() : Rotation(0, 0, 0) {}

        float Pitch, Yaw, Roll;
        mutable Matrix4f CacheInv;
        mutable Matrix4f PMat, YMat, RMat;
        mutable uint8_t PitchDirty: 1;
        mutable uint8_t YawDirty: 1;
        mutable uint8_t RollDirty: 1;
        mutable uint8_t InvDirty: 1;
        mutable uint8_t MatDirty: 1;

        float GetPitch() const { return Pitch; }

        float GetYaw() const { return Yaw; }

        float GetRoll() const { return Roll; }

        void SetPitchDirty() {
            PitchDirty = true;
            InvDirty = true;
            MatDirty = true;
        }
        void SetYawDirty() {
            YawDirty = true;
            InvDirty = true;
            MatDirty = true;
        }
        void SetRollDirty() {
            RollDirty = true;
            InvDirty = true;
            MatDirty = true;
        }

        void SetPitch(float rad) { SetPitchWithDegree(math::Rad2Deg(rad)); }

        void SetPitchWithDegree(float degree) {
            degree = math::Clamp(degree, -90.f, 90.f);
            Pitch = math::Deg2Rad(degree);
            SetPitchDirty();
        }

        void SetYaw(float rad) { SetYawWithDegree(math::Rad2Deg(rad)); }

        void SetYawWithDegree(float degree) {
            if (degree > 360) { degree -= 360.f * (float) (int) (degree / 360.f); }
            if (degree < 0) { degree += 360.f * (float) (1 + (int) (-degree / 360.f)); }
            Yaw = math::Deg2Rad(degree);
            SetYawDirty();
        }

        const Matrix4f &GetPitchMatrix() const {
            if (PitchDirty) {
                PMat = PitchMat(Pitch);
                PitchDirty = false;
            }
            return PMat;
        }

        const Matrix4f &GetYawMatrix() const {
            if (YawDirty) {
                YMat = YawMat(Yaw);
                YawDirty = false;
            }
            return YMat;
        }

        const Matrix4f &GetRollMatrix() const {
            if (RollDirty) {
                RMat = RollMat(Roll);
                RollDirty = false;
            }
            return RMat;
        }

        const Matrix4f &GetInv() const {
            if (InvDirty) {
                CacheInv = GetPitchMatrix().T() * GetYawMatrix().T() * GetRollMatrix().T();
                InvDirty = false;
            }
            return CacheInv;
        }

        const Matrix4f &GetMat() const {
            if (MatDirty) {
                Mat = GetRollMatrix() * GetYawMatrix() * GetPitchMatrix();
                MatDirty = false;
            }
            return Mat;
        }

        /// operation support

        operator const Matrix4f &() const { return GetMat(); }

        Matrix4f operator*(const Matrix4f &rhs) const { return GetMat() * rhs; }

        glm::vec4 operator*(const glm::vec4 &rhs) const { return GetMat() * rhs; }
    };
};
