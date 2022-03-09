import { getUserLocale } from '../lib/get-user-locale'

describe('getUserLocale', () => {
  it('works', () => {
    const locale = getUserLocale()
    expect(locale).not.toBeUndefined()
    expect(typeof locale).toBe('string')
    expect(locale).toMatch(/^[a-z]{2}-[A-Z]{2}$/)
  })
})
