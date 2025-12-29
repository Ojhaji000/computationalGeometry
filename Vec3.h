class Vec3{
    public:
        float x, y, z;
        Vec3();
        Vec3(const float &X, const float &Y, const float &Z);
        Vec3 operator+(const Vec3 &b);
        Vec3 operator-(const Vec3 &b);
        Vec3 operator*(float &scalar);
        float dot(const Vec3 &b);
        Vec3 cross(Vec3 &b);
};