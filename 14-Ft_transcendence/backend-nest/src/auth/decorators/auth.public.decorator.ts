import { SetMetadata } from '@nestjs/common';

/**
 * Public endpoints are endpoints that require no authentication.
 */
export const IS_PUBLIC_ENDPOINT: string = 'IS_PUBLIC_ENDPOINT';
export const Public = () => SetMetadata(IS_PUBLIC_ENDPOINT, true);
