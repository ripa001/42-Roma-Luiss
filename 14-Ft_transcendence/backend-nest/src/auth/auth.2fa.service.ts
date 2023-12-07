import { HttpException, HttpStatus, Injectable } from '@nestjs/common';
import { generateSecret, verify } from '2fa-util';
import { PlayersService } from 'src/players/players.service';

const debug = false

@Injectable()
export class TwoFaService {
	private unconfirmed_secrets: Map<number, string> = new Map<number, string>();

	constructor(private readonly pservice: PlayersService) {}

	async verifyOTP(userID: number, otp: string): Promise<boolean> {
		let secret: string;

		if (this.unconfirmed_secrets.has(userID)) {
			secret = this.unconfirmed_secrets.get(userID);
			if (debug) console.log('DEBUG | auth.2fa.service | verifyOTP | secret : ' + secret)
			if (true == (await verify(otp, secret))) {
				this.pservice.update(userID, { twofaSecret: secret });
				this.unconfirmed_secrets.delete(userID);
				return true;
			}
			return false;
		} else {
			secret = (await this.pservice.findOne(userID)).twofaSecret;
			if (debug) console.log('DEBUG | auth.2fa.service | verifyOTP | secret : ' + secret)
			if (secret && true == (await verify(otp, secret))) {
					return true;
				}
			return false;
		}
	}

	async removeOTP(userID: number, otp: string): Promise<boolean> {
		try {
			if (true == (await this.verifyOTP(userID, otp))) {
				await this.pservice.update(userID, {
					twofaSecret: null
				})
				return true;
			}
			return false;
		}
		catch (error) {
			throw new HttpException('Internal Server Error', HttpStatus.INTERNAL_SERVER_ERROR);
		}
	}


	async generate2FAQRCode(userID: number): Promise<string> {
		const { qrcode, secret } = await generateSecret(
			String(userID),
			process.env.APP_NAME,
		);
		this.unconfirmed_secrets.set(userID, secret);
		return qrcode;
	}
}
