import { ExecutionContext, Injectable } from '@nestjs/common';
import { AuthGuard } from '@nestjs/passport';

@Injectable()
export class FortyTwoAuthGuard extends AuthGuard('42') {
	constructor() {
		super();
	}

	async canActivate(context: ExecutionContext): Promise<boolean> {
		try {
			if (await super.canActivate(context)) return true;
		} catch (_) {
			return false;
		}
	}
}
