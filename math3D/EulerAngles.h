#ifndef __EulerAngles_H_
#define __EulerAngles_H_


class EulerAngles {
public:
	EulerAngles(float const &heading = 0, float const &pitch = 0, float const &bank = 0);

	const double *heading() const {
		return &_heading;
	}
	void heading(double const &value);

	const double *pitch() const {
		return &_pitch;
	}
	void pitch(double const &value);

	const double *bank() const {
		return &_bank;
	}
	void bank(double const &value);

	bool isCanonical() const;

	void canonize();

private:
	double _heading;
	double _pitch;
	double _bank;
};


#endif //__EulerAngles_H_
