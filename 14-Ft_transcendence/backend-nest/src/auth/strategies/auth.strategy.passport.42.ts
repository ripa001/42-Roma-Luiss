import { Injectable } from '@nestjs/common';
import { PassportStrategy } from '@nestjs/passport';
import { Strategy } from 'passport-42';

const debug = true

@Injectable()
export class FortyTwoStrategy extends PassportStrategy(Strategy, '42') {
	constructor() {
		super({
			clientID: process.env.UID,
			clientSecret: process.env.SECRET,
			callbackURL: process.env.CALLBACK_URL,
		});
        if (debug) console.log('DEBUG | auth.strategy | constructor() : called');
	}

	async validate(
		accessToken: string,
		refreshToken: string,
		profile: any,
		done: (error: any, profile: any) => any,
	) {
        if (debug) console.log('DEBUG | auth.strategy | validate() : called');

		// store profile in req.user
		const user = {
			id: Number(profile.id),
			username: profile.username,
			avatar: process.env.BACKEND_DEFAULT_PFP,
			firstName: profile.name.givenName,
			lastName: profile.name.familyName,
			profileIntra: profile.profileUrl,
		};

		done(null, user);
	}
}
