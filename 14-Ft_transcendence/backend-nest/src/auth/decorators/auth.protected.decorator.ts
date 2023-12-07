import { SetMetadata } from '@nestjs/common';

/**
 * Protected endpoints are endpoints that require only one level of authentication.
 */
export const IS_PROTECTED_ENDPOINT: string = 'IS_PROTECTED_ENDPOINT';
export const Protected = () => SetMetadata(IS_PROTECTED_ENDPOINT, true);
